#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    // 初始化限流时长
    m_defaultMinIntervalMs = 1000;
    m_hostLimits[u"www.luogu.com.cn"_s].minIntervalMs = 3000; // 主站严格限流
    m_hostLimits[u"cdn.luogu.com.cn"_s].minIntervalMs = 500;  // CDN 快速
    // 初始化 MethodMap
    MethodMap[RequestMethod::Get] = HTTP_GET;
    MethodMap[RequestMethod::Post] = HTTP_POST;
    MethodMap[RequestMethod::Put] = HTTP_PUT;
    MethodMap[RequestMethod::Delete] = HTTP_DELETE;
    MethodMap[RequestMethod::Head] = HTTP_HEAD;
    MethodMap[RequestMethod::Options] = HTTP_OPTIONS;
    MethodMap[RequestMethod::Patch] = HTTP_PATCH;
    // 将 NetworkManager 移动到工作线程
    this->moveToThread(&m_workerThread);
    // 启动工作线程
    m_workerThread.start();
    // 定时器在工作线程中运行，用于周期性调度请求
    m_timer.setInterval(100); // 每 100ms 检查一次队列
    m_timer.moveToThread(&m_workerThread);
    // 连接定时器信号到调度函数
    connect(&m_timer, &QTimer::timeout, this, &NetworkManager::processNext);
    // 在工作线程中启动定时器
    QMetaObject::invokeMethod(&m_timer, "start", Qt::QueuedConnection);
}

NetworkManager::~NetworkManager()
{
    // 停止定时器
    QMetaObject::invokeMethod(&m_timer, "stop", Qt::QueuedConnection);
    // 请求线程退出
    m_workerThread.quit();
    // 等待线程完全结束
    m_workerThread.wait();
    // 清空队列（线程安全）
    {
        QMutexLocker locker(&m_queueMutex);
        while (!m_queue.empty())
        {
            m_queue.pop();
        }
    }
}

void NetworkManager::enqueueRequest(const NetworkRequest &req)
{
    // 记录提交时间，用于 FIFO 排序
    NetworkRequest copy = req;
    copy.submitTime = QDateTime::currentDateTime();
    {
        QMutexLocker locker(&m_queueMutex);
        m_queue.push(copy);
    }
    // 唤醒工作线程，让它尽快处理队列
    QMetaObject::invokeMethod(this, "processNext", Qt::QueuedConnection);
}

NetworkResponse NetworkManager::blockingRequest(const NetworkRequest &req)
{
    // 用于接收结果
    NetworkResponse result;
    bool finished = false;
    // 创建事件循环
    QEventLoop loop;
    // 创建一个临时请求副本
    NetworkRequest copy = req;
    // 为这个请求设置一个专用回调
    copy.callback = [&](NetworkResponse data)
    {
        result = data;
        finished = true;
        loop.quit(); // 退出事件循环
    };
    // 入队（异步）
    enqueueRequest(copy);
    // 堵塞当前线程
    loop.exec();
    return result; // 返回空响应作为占位
}

NetworkResponse NetworkManager::sendRequest(const NetworkRequest &req)
{
    HttpRequest tmp;
    tmp.method = MethodMap[req.method];
    tmp.url = req.finalUrl().toStdString();
    tmp.redirect = 0;
    for (auto it = req.headers.constBegin(); it != req.headers.constEnd(); ++it)
        tmp.headers[it.key().toStdString()] = it.value().toStdString();
    tmp.body = req.payload;
    m_cookieJar.applyToRequest(tmp);
    HttpResponse resp;
    int res = http_client_send(&tmp, &resp);
    NetworkResponse net;
    if (res != 0)
    {
        // 网络层失败，没有 HTTP 响应
        net.statusCode = -1;
        net.timestamp = QDateTime::currentDateTime();
        return net;
    }
    // 状态码
    net.statusCode = resp.status_code;
    // body
    net.body = QByteArray::fromStdString(resp.body);
    // headers
    for (const auto &kv : resp.headers)
    {
        net.headers.insert(
            QString::fromStdString(kv.first),
            QString::fromStdString(kv.second));
    }
    // cookie
    m_cookieJar.updateFromResponse(resp);
    // 时间戳
    net.timestamp = QDateTime::currentDateTime();
    return net;
}

void NetworkManager::processNext()
{
    NetworkRequest req;
    {
        // 加锁保护队列
        QMutexLocker locker(&m_queueMutex);
        if (m_queue.empty())
            return;
        // 取出最高优先级的请求
        req = m_queue.top();
        m_queue.pop();
    }
    const QDateTime now = QDateTime::currentDateTime();
    const QString host = req.host;
    // ================================
    // 0. 限流检查（按 host）
    // ================================
    {
        QMutexLocker locker(&m_hostMutex);
        // 自动插入未知 host，使用默认限流
        auto it = m_hostLimits.find(host);
        if (it == m_hostLimits.end())
        {
            HostRateLimit limit;
            limit.minIntervalMs = m_defaultMinIntervalMs;
            limit.lastRequestTime = QDateTime(); // 无效时间
            it = m_hostLimits.insert(host, limit);
        }
        HostRateLimit &limit = it.value();
        if (!limit.lastRequestTime.isValid())
        {
            // 第一次请求这个 host，直接放行，并记录时间
            limit.lastRequestTime = now;
        }
        else
        {
            qint64 elapsed = limit.lastRequestTime.msecsTo(now);
            if (elapsed < limit.minIntervalMs)
            {
                // 还没到时间 → 把请求放回队列
                qDebug() << limit.lastRequestTime;
                qDebug() << "[INFO] Network Manager: [Rate Limit] Time since last request is " << elapsed << "ms, rate-limit interval is " << limit.minIntervalMs << "ms.";
                QMutexLocker locker2(&m_queueMutex);
                m_queue.push(req);
                return;
            }
            // 更新该 host 的最后请求时间
            limit.lastRequestTime = now;
        }
    }
    // ================================
    // 1. 在工作线程执行同步网络请求
    // ================================
    NetworkResponse response = sendRequest(req);
    // ================================
    // 2. 执行 callback
    // ================================
    if (req.callback)
        req.callback(response);
    // ================================
    // 3. 发出异步信号（对外 API）
    // ================================
    Q_EMIT requestFinished(response, req.requestId);
}
