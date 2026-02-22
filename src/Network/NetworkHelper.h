#pragma once
#include "Network/NetworkManager.h"
#include <QString>

using namespace Qt::StringLiterals;

class NetworkHelper
{
public:
    explicit NetworkHelper(NetworkManager *network);
    static const QString USER_AGENT;

    // ===== 浏览器请求头 =====

    // 一般网页请求头
    static QMap<QString, QString> browserHeaders();
    // 图片请求头
    static QMap<QString, QString> browserImageHeaders();
    // JSON 请求头
    static QMap<QString, QString> browserJsonHeaders(bool includeContentType = true);

    // ===== 自动重定向 =====
    NetworkResponse followRedirects(NetworkRequest req, const int retryLimit = 3);

    // ===== 快速初始化请求 =====

    // GET 请求
    NetworkRequest get(const QString &url, const QMap<QString, QString> &headers = {});
    // POST 请求
    NetworkRequest post(const QString &url, const QByteArray &payload, const QMap<QString, QString> &headers = {});

private:
    NetworkManager *m_network;
};
