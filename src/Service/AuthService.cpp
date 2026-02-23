#include "AuthService.h"

AuthService::AuthService(AuthRepository *authRepo, UserRepository *userRepo, QObject *parent)
    : QObject(parent), m_authRepo(authRepo), m_userRepo(userRepo)
{
}

void AuthService::login(const QString &username, const QString &password, const QString &captcha)
{
    // 异步调用
    QMetaObject::invokeMethod(
        this,
        [=]()
        {
            AuthResult loginResult = m_authRepo->login(username, password, captcha);
            if (!loginResult.success)
            {
                Q_EMIT loginFailed(loginResult.errorMessage);
                return;
            }
            m_loggedIn = true;
            Q_EMIT loginSucceeded();
            Q_EMIT loggedInChanged();
            m_currentUser = m_userRepo->fetchUser(loginResult.uid);
            Q_EMIT currentUserChanged();
        },
        Qt::QueuedConnection);
}

void AuthService::logout()
{
    // 异步调用
    QMetaObject::invokeMethod(
        this,
        [=]()
        {
            AuthResult logoutResult = m_authRepo->logout();
            if (!logoutResult.success)
            {
                Q_EMIT loginFailed(logoutResult.errorMessage);
                return;
            }
            m_loggedIn = false;
            m_currentUser = User();
            Q_EMIT logoutSucceeded();
            Q_EMIT loggedInChanged();
        },
        Qt::QueuedConnection);
}

bool AuthService::isLoggedIn() const
{
    return m_loggedIn;
}

const User &AuthService::currentUser() const
{
    return m_currentUser;
}

void AuthService::refreshCurrentUser()
{
    // 异步调用
    QMetaObject::invokeMethod(
        this,
        [=]()
        {
            User user = m_userRepo->fetchUser(m_currentUser.profile.uid);
            if (!m_loggedIn)
                return;
            if (user.profile.uid == 0)
                return;
            if (user != m_currentUser)
            {
                m_currentUser = user;
                Q_EMIT currentUserChanged();
            }
        },
        Qt::QueuedConnection);
}

void AuthService::refreshCaptcha()
{
    // 异步调用
    QMetaObject::invokeMethod(
        this,
        [=]()
        {
            QByteArray data = m_authRepo->fetchCaptcha();
            if (data.isEmpty())
                return;

            QImage image;
            image.loadFromData(data);
            if (image.isNull())
                Q_EMIT captchaRefreshed(image);
        },
        Qt::QueuedConnection);
}
