#include "UserRepository.h"

UserRepository::UserRepository(NetworkManager *network)
    : m_network(network)
{
}

User UserRepository::fetchUser(int uid)
{
    NetworkRequest req(u"https://www.luogu.com.cn/user/%1"_s.arg(uid));
    req.method = RequestMethod::Get;
    QMap<QString, QString> Headers;
    Headers[u"User-Agent"_s] = u"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/145.0.0.0 Safari/537.36"_s;
    Headers[u"Accept"_s] = u"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"_s;
    req.headers = Headers;
    NetworkResponse res = m_network->blockingRequest(req);
    if (res.statusCode == 200)
        return analyzeUserResponse(res.body);
    else if (res.statusCode == 302)
    {
        for (int i = 0; i < RETRY_LIMIT; ++i)
        {
            qDebug() << u"[INFO] User Repository: [User Fetch] Redirect to %1"_s.arg(res.headers[u"Location"_s]).toStdString().c_str();
            req.finalUrl() = res.headers[u"Location"_s];
            res = m_network->blockingRequest(req);
            if (res.statusCode == 200)
                return analyzeUserResponse(res.body);
        }
    }
    else if (res.statusCode == 404)
    {
        // 用户不存在
        qDebug() << u"[ERROR] User Repository: [User Fetch] User with uid %1 does not exist."_s.arg(uid).toStdString().c_str();
        return User();
    }
    else
    {
        // 其他错误
        qDebug() << res.statusCode;
        qDebug() << res.body;
        qDebug() << u"[ERROR] User Repository: [User Fetch] An error occurred while fetching user with uid %1."_s.arg(uid).toStdString().c_str();
        return User();
    }
    return User();
}

User UserRepository::analyzeUserResponse(const QByteArray &res)
{
    QRegularExpression re(uR"(<script\s+id="lentille-context"[^>]*>([\s\S]*?)<\/script>)"_s);
    auto match = re.match(QString::fromUtf8(res));
    if (match.hasMatch())
    {
        auto json = QJsonDocument::fromJson(match.captured(1).toUtf8());
        auto u = json.object()[u"data"_s].toObject();
        if (u.isEmpty())
        {
            qDebug() << "[ERROR] User Repository: [User Fetch Response Analyze] Unable to parse user data, as the \"data\" field is empty or not exist.";
            qDebug() << json;
            return User();
        }
        qDebug() << u;
        return User::fromJson(u);
    }
    else
    {
        qDebug() << "[ERROR] User Repository: [User Fetch Response Analyze] Unable to parse user data, as the response body does not match the expected format.";
        return User();
    }
}
