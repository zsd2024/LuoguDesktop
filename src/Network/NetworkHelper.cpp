#include "NetworkHelper.h"

NetworkHelper::NetworkHelper(NetworkManager *network)
    : m_network(network)
{
}

const QString NetworkHelper::USER_AGENT = u"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/145.0.0.0 Safari/537.36"_s;

QMap<QString, QString> NetworkHelper::browserHeaders()
{
    QMap<QString, QString> headers;
    headers[u"User-Agent"_s] = USER_AGENT;
    headers[u"Accept"_s] = u"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"_s;
    return headers;
}

QMap<QString, QString> NetworkHelper::browserImageHeaders()
{
    QMap<QString, QString> headers;
    headers[u"User-Agent"_s] = USER_AGENT;
    headers[u"Accept"_s] = u"image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8"_s;
    return headers;
}

QMap<QString, QString> NetworkHelper::browserJsonHeaders(bool includeContentType)
{
    QMap<QString, QString> headers;
    headers[u"User-Agent"_s] = USER_AGENT;
    headers[u"Accept"_s] = u"application/json, text/plain, */*"_s;
    if (includeContentType)
        headers[u"Content-Type"_s] = u"application/json"_s;
    return headers;
}

NetworkResponse NetworkHelper::followRedirects(NetworkRequest req, const int retryLimit)
{
    NetworkResponse res = m_network->blockingRequest(req);
    if (res.statusCode == 302 || res.statusCode == 307)
    {
        for (int i = 0; i < retryLimit; ++i)
        {
            const QString location = res.headers[u"Location"_s];
            if (location.isEmpty())
                return res; // 这……不对吧
            req.setUrl(location);
            res = m_network->blockingRequest(req);
            if (res.statusCode == 200)
                break;
            else if (res.statusCode == 302 || res.statusCode == 307)
                continue;
            else
                return res;
        }
        if (res.statusCode != 200)
            return res;
    }
    return res;
}

NetworkRequest NetworkHelper::get(const QString &url, const QMap<QString, QString> &headers)
{
    NetworkRequest req(url);
    req.method = RequestMethod::Get;
    req.headers = headers;
    return req;
}

NetworkRequest NetworkHelper::post(const QString &url, const QByteArray &payload, const QMap<QString, QString> &headers)
{
    NetworkRequest req(url);
    req.method = RequestMethod::Post;
    req.headers = headers;
    req.payload = payload;
    return req;
}
