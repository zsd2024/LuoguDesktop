#pragma once
#include "NetworkRequest.h"
#include "NetworkResponse.h"
#include <QDateTime>
#include <QMap>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <hv/HttpClient.h>
#include <queue>

using namespace Qt::StringLiterals;

// 每个 host 的限流状态
struct HostRateLimit
{
    QDateTime lastRequestTime;
    int minIntervalMs = 100; // 默认 100ms，可按 host 调整
};

struct RequestComparator
{
    bool operator()(const NetworkRequest &a, const NetworkRequest &b) const
    {
        if (a.priority == b.priority)
        {
            // 优先级相同，按提交时间排序（先提交的先执行）
            return a.submitTime > b.submitTime;
        }
        // 优先级高的排在前面
        return a.priority < b.priority;
    }
};

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    // 构造函数：可被 QML 调用（Q_INVOKABLE），parent 默认为 nullptr
    Q_INVOKABLE explicit NetworkManager(QObject *parent = nullptr);

    // 析构函数：负责清理线程与队列等资源
    ~NetworkManager();

    // 异步提交请求：将请求放入优先级队列（线程安全）
    Q_INVOKABLE void enqueueRequest(const NetworkRequest &req);

    // 同步阻塞接口：在调用者线程中阻塞直到请求完成（慎用于 UI 线程）
    Q_INVOKABLE NetworkResponse blockingRequest(const NetworkRequest &req);

Q_SIGNALS:

    // 注意：如果这是信号，应写为: signals: void requestFinished(const NetworkResponse &result);
    void requestFinished(const NetworkResponse &result, const QString &requestId);

    // 异步错误通知（同上，实际应为 signal）
    void requestError(const QString &host, const QString &message, const QString &requestId);

private:
    // 方法映射表：将自定义的 RequestMethod 映射到 libhv 的 http_method
    QMap<RequestMethod, http_method> MethodMap;

    // 优先级队列：存放待处理的 NetworkRequest，使用 RequestComparator 比较优先级
    std::priority_queue<NetworkRequest, std::vector<NetworkRequest>, RequestComparator> m_queue;

    // 保护队列与相关状态的互斥锁，保证多线程访问安全
    QMutex m_queueMutex;

    // 记录每个 host 上次请求时间，用于实现每个 host 至少间隔 3 秒的限制
    QMap<QString, QDateTime> m_lastRequestTime;

    // 工作线程：NetworkManager 的调度与执行逻辑运行在此线程中（通过 moveToThread）
    QThread m_workerThread;

    // 调度定时器：定期触发 processNext() 检查并执行队列中的请求
    QTimer m_timer;

    // 自定义发送函数：将 NetworkRequest 转换为实际网络操作并返回响应（同步实现）
    NetworkResponse sendRequest(const NetworkRequest &req);

    // 调度函数：从队列中取出符合限流条件的请求并执行
    Q_INVOKABLE void processNext();

    // 配置各个 host 的限流
    QMap<QString, HostRateLimit> m_hostLimits;

    // 保护限流配置与相关状态的互斥锁，保证多线程访问安全
    QMutex m_hostMutex;

    // 默认限流时长
    int m_defaultMinIntervalMs;
};
