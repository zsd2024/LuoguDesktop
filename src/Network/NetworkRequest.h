#pragma once
#include "NetworkResponse.h"
#include "RequestMethod.h"
#include <QDateTime>
#include <QMap>

using namespace Qt::StringLiterals;

class NetworkRequest
{
public:
    enum class Scheme
    {
        Http,
        Https
    };

public:
    // 构造函数：传入完整 URL
    explicit NetworkRequest(const QString &fullUrl);

    // 构造函数：传入 host + path
    NetworkRequest(const QString &host,
                   const QString &path,
                   RequestMethod method = RequestMethod::Get,
                   int priority = 0);

    // 默认构造
    NetworkRequest() = default;

    // 标准化 host/path 并解析协议
    void normalize();

    // 构造最终 URL
    QString finalUrl() const;

    // 设置 URL
    void setUrl(QString fullUrl);

public:
    int priority = 0;                              // 优先级（越大越优先）
    QString host;                                  // 目标主机（不含协议、不含路径）
    QString path;                                  // 路径（必须以 "/" 开头）
    QByteArray payload;                            // 请求数据（POST/PUT）
    QMap<QString, QString> headers;                // 请求头
    RequestMethod method = RequestMethod::Get;     // 请求方法
    std::function<void(NetworkResponse)> callback; // 异步回调
    QString requestId;                             // 唯一标识符
    QDateTime submitTime;                          // 提交时间（用于 FIFO 排序）
    Scheme scheme = Scheme::Https;                 // 协议（默认 https）
};
