#include "CookieJar.h"

void CookieJar::updateFromResponse(const HttpResponse &resp)
{
    QMutexLocker locker(&m_mutex);
    auto list = resp.cookies;
    for (const HttpCookie &cookie : list)
    {
        auto it = std::remove_if(m_cookies.begin(), m_cookies.end(), [&](const HttpCookie &c)
                                 { return c.name == cookie.name && c.domain == cookie.domain && c.path == cookie.path; });
        m_cookies.erase(it, m_cookies.end());
        m_cookies.push_back(cookie);
    }
}

void CookieJar::applyToRequest(HttpRequest &req) const
{
    QMutexLocker locker(&m_mutex);
    for (const auto &cookie : m_cookies)
        req.AddCookie(cookie);
}

void CookieJar::clear()
{
    QMutexLocker locker(&m_mutex);
    m_cookies.clear();
}
