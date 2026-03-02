#include "AuthRepository.h"

using namespace Qt::StringLiterals;

AuthRepository::AuthRepository(NetworkManager *network)
    : m_network(network), m_helper(network)
{
}

QString AuthRepository::extractCsrfToken(const QByteArray &res)
{
    QRegularExpression re(uR"raw(<meta\s+name="csrf-token"\s+content="([^"]+)">)raw"_s);
    auto match = re.match(QString::fromUtf8(res));
    if (match.hasMatch())
        return match.captured(1);
    return {};
}

AuthResult AuthRepository::login(const QString &username, const QString &password, const QString &captcha)
{
    NetworkResponse res = m_helper.followRedirects(m_helper.get(u"https://www.luogu.com.cn/auth/login"_s, m_helper.browserHeaders()), RETRY_LIMIT);
    QString csrfToken;
    if (res.statusCode == 200)
    {
        csrfToken = extractCsrfToken(res.body);
        if (csrfToken.isEmpty())
            return {false, u"无法获取 CSRF 令牌"_s, -1, u"LuoguDesktop\\Auth\\Exception\\CsrfTokenCannotBeExtractedException"_s};
    }
    else
        return {false, u"网络请求失败"_s, res.statusCode, u"LuoguDesktop\\Network\\Exception\\HttpException"_s};
    qDebug() << csrfToken;
    QJsonObject payload{
        {u"username"_s, username},
        {u"password"_s, password},
        {u"captcha"_s, captcha}};
    QByteArray payloadStr = QJsonDocument(payload).toJson(QJsonDocument::Compact);
    QMap<QString, QString> loginHeaders = m_helper.browserJsonHeaders();
    loginHeaders[u"X-CSRF-Token"_s] = csrfToken;
    NetworkResponse loginRes = m_network->blockingRequest(m_helper.post(u"https://www.luogu.com.cn/do-auth/password"_s, payloadStr, loginHeaders));
    qDebug() << loginRes.body;
    if (loginRes.statusCode == 200)
    {
        std::optional<QString> uidOpt = m_network->cookieJar()->getCookie(u"_uid"_s);
        int uid = uidOpt ? uidOpt->toInt() : 0;
        if (uid == 0)
            qDebug() << u"[ERROR] Auth Repository: [Login] Cannot get uid from cookie, which \"_uid\" is %0. "_s.arg(uidOpt.value_or(u"null"_s)).toStdString().c_str();
        else
            qDebug() << u"[INFO] Auth Repository: [Login] Successfully logged in as user with uid %0. "_s.arg(uid).toStdString().c_str();
        return {true, {}, 200, {}, uid};
    }
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
    NetworkResponse res = m_network->blockingRequest(m_helper.get(u"https://www.luogu.com.cn/auth/logout"_s, m_helper.browserHeaders()));
    if (res.statusCode == 302)
        return {true, {}, 200, {}};
    else
        return {false, u"未知错误"_s, -1, {}};
}

QByteArray AuthRepository::fetchCaptcha()
{
    // 先访问一次主站获取 Cookie
    NetworkResponse res = m_helper.followRedirects(m_helper.get(u"https://www.luogu.com.cn/"_s, m_helper.browserHeaders()), RETRY_LIMIT);
    if (res.statusCode != 200)
        return {};

    NetworkResponse captchaRes = m_helper.followRedirects(m_helper.get(u"https://www.luogu.com.cn/lg4/captcha"_s, m_helper.browserImageHeaders()), RETRY_LIMIT);
    if (captchaRes.statusCode == 200)
        return captchaRes.body;
    else
        return QByteArray();
}
