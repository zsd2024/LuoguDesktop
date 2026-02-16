#include "NetworkRequest.h"

// ============================
// 构造函数：传入完整 URL
// ============================
NetworkRequest::NetworkRequest(QString fullUrl)
{
    fullUrl = fullUrl.trimmed();

    // 解析协议
    if (fullUrl.startsWith(u"http://"_s))
    {
        scheme = Scheme::Http;
        fullUrl = fullUrl.mid(7);
    }
    else if (fullUrl.startsWith(u"https://"_s))
    {
        scheme = Scheme::Https;
        fullUrl = fullUrl.mid(8);
    }

    // 分离 host 与 path
    int slash = fullUrl.indexOf(u"/"_s);

    if (slash < 0)
    {
        host = fullUrl;
        path = u"/"_s;
    }
    else
    {
        host = fullUrl.left(slash);
        path = fullUrl.mid(slash);
    }

    normalize();
}

// ============================
// 构造函数：host + path
// ============================
NetworkRequest::NetworkRequest(QString host,
                               QString path,
                               RequestMethod method,
                               int priority)
    : priority(priority),
      host(std::move(host)),
      path(std::move(path)),
      method(method)
{
    normalize();
}

// ============================
// 标准化 host/path
// ============================
void NetworkRequest::normalize()
{
    // ---- host ----
    host = host.trimmed();

    while (host.endsWith(u"/"_s))
        host.chop(1);

    if (host.isEmpty())
        host = u"localhost"_s;

    // ---- path ----
    if (path.isEmpty())
    {
        path = u"/"_s;
    }
    else
    {
        path = path.trimmed();

        if (!path.startsWith(u"/"_s))
            path.prepend(u"/"_s);

        if (path.length() > 1 && path.endsWith(u"/"_s))
            path.chop(1);

        while (path.contains(u"//"_s))
            path.replace(u"//"_s, u"/"_s);
    }
}

// ============================
// 构造最终 URL
// ============================
QString NetworkRequest::finalUrl() const
{
    return (scheme == Scheme::Https ? u"https://"_s : u"http://"_s) + host + path;
}
