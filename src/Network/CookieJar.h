#pragma once
#include <QMutex>
#include <hv/HttpMessage.h>

class CookieJar
{
public:
    CookieJar() = default;

    // 从响应中更新 cookie
    void updateFromResponse(const HttpResponse &resp);

    // 在请求前注入 cookie
    void applyToRequest(HttpRequest &req) const;

    // 清空所有 cookie
    void clear();

private:
    http_cookies m_cookies;
    mutable QMutex m_mutex;
};
