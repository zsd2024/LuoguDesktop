#pragma once
#include "Network/NetworkHelper.h"
#include "Network/NetworkManager.h"
#include <QDir>
#include <QJsonObject>
#include <QRegularExpression>
#include <QString>

struct AuthResult
{
    bool success;
    QString errorMessage; // 错误信息（UI 使用）
    int errorCode;        // 错误码（判断使用）
    QString errorType;    // 错误类型（判断使用）
    int uid = 0;          // 用户 ID（仅在登录成功时有效）
};

class AuthRepository
{
public:
    explicit AuthRepository(NetworkManager *network);
    AuthResult login(const QString &username, const QString &password, const QString &captcha);
    AuthResult logout();
    QByteArray fetchCaptcha();

private:
    QString extractCsrfToken(const QByteArray &res);
    NetworkManager *m_network;
    NetworkHelper m_helper;
    const int RETRY_LIMIT = 3;
};
