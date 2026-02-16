#pragma once
#include <QByteArray>
#include <QDateTime>
#include <QMap>
#include <QString>

using namespace Qt::StringLiterals;

class NetworkResponse
{
public:
    NetworkResponse() = default;

public:
    int statusCode = 0;             // HTTP 状态码（200/404/500…）
    QByteArray body;                // 响应体
    QMap<QString, QString> headers; // 响应头
    QDateTime timestamp;            // 响应时间
};
