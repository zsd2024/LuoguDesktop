#include "AuthRepository.h"

AuthRepository::AuthRepository(NetworkManager *network)
    : m_network(network)
{
}

QString AuthRepository::extractCsrfToken(const QByteArray &res)
{
    // <meta name="csrf-token" content="1771682486:fr/34+sxFPey/2ZWKY9thvixAAUm6ZAnfMEe11je8RQ=">
    QRegularExpression re(uR"raw(<meta\s+name="csrf-token"\s+content="([^"]+)">)raw"_s);
    auto match = re.match(QString::fromUtf8(res));
    if (match.hasMatch())
        return match.captured(1);
    return {};
}

AuthResult AuthRepository::login(const QString &username, const QString &password, const QString &captcha)
{
    NetworkRequest req(u"https://www.luogu.com.cn/auth/login"_s);
    req.method = RequestMethod::Get;
    QMap<QString, QString> Headers;
    Headers[u"User-Agent"_s] = u"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/145.0.0.0 Safari/537.36"_s;
    Headers[u"Accept"_s] = u"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"_s;
    req.headers = Headers;
    NetworkResponse res = m_network->blockingRequest(req);
    QString csrfToken;
    if (res.statusCode == 200)
    {
        csrfToken = extractCsrfToken(res.body);
        if (csrfToken.isEmpty())
            return {false, u"无法获取 CSRF 令牌"_s, -1, u"LuoguDesktop\\Auth\\Exception\\CsrfTokenCannotBeExtractedException"_s};
    }
    else if (res.statusCode == 302)
    {
        for (int i = 0; i < RETRY_LIMIT; ++i)
        {
            req.finalUrl() = res.headers[u"Location"_s];
            res = m_network->blockingRequest(req);
            if (res.statusCode == 200)
            {
                csrfToken = extractCsrfToken(res.body);
                if (!csrfToken.isEmpty())
                    break;
                return {false, u"无法获取 CSRF 令牌"_s, -1, u"LuoguDesktop\\Auth\\Exception\\CsrfTokenCannotBeExtractedException"_s};
            }
            else if (res.statusCode == 302)
                continue;
            else
                return {false, u"网络请求失败"_s, res.statusCode, u"LuoguDesktop\\Network\\Exception\\HttpException"_s};
        }
        if (csrfToken.isEmpty())
            return {false, u"网络请求失败"_s, res.statusCode, u"LuoguDesktop\\Network\\Exception\\HttpException"_s};
    }
    else
        return {false, u"网络请求失败"_s, res.statusCode, u"LuoguDesktop\\Network\\Exception\\HttpException"_s};
    qDebug() << csrfToken;
    NetworkRequest loginReq(u"https://www.luogu.com.cn/do-auth/password"_s);
    loginReq.method = RequestMethod::Post;
    loginReq.headers[u"User-Agent"_s] = u"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/145.0.0.0 Safari/537.36"_s;
    loginReq.headers[u"Accept"_s] = u"application/json, text/plain, */*"_s;
    loginReq.headers[u"Content-Type"_s] = u"application/json"_s;
    loginReq.headers[u"X-CSRF-Token"_s] = csrfToken;
    QJsonObject payload{
        {u"username"_s, username},
        {u"password"_s, password},
        {u"captcha"_s, captcha}};
    loginReq.payload = QJsonDocument(payload).toJson(QJsonDocument::Compact);
    NetworkResponse loginRes = m_network->blockingRequest(loginReq);
    qDebug() << loginRes.body;
    if (loginRes.statusCode == 200)
        return {true, {}, 200, {}};
    else
    {
        QJsonObject json = QJsonDocument::fromJson(loginRes.body).object();
        if (json.empty())
            return {false, u"未知错误"_s, -1, {}};
        else
            return {false, json[u"errorMessage"_s].toString(), json[u"errorCode"_s].toInt(), json[u"errorType"_s].toString()};
    }
}

AuthResult AuthRepository::logout()
{
    NetworkRequest req(u"https://www.luogu.com.cn/auth/logout"_s);
    req.method = RequestMethod::Get;
    QMap<QString, QString> Headers;
    Headers[u"User-Agent"_s] = u"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/145.0.0.0 Safari/537.36"_s;
    Headers[u"Accept"_s] = u"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"_s;
    req.headers = Headers;
    NetworkResponse res = m_network->blockingRequest(req);
    if (res.statusCode == 302)
        return {true, {}, 200, {}};
    else
        return {false, u"未知错误"_s, -1, {}};
}
