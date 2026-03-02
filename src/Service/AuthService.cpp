#include "AuthService.h"

AuthService::AuthService(AuthRepository *authRepo, UserRepository *userRepo, QObject *parent)
    : QObject(parent), m_authRepo(authRepo), m_userRepo(userRepo), m_currentUserWrapper(new UserWrapper(this))
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
            User user = m_userRepo->fetchUser(loginResult.uid);
            updateCurrentUser(std::move(user));
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
            updateCurrentUser(User());
            Q_EMIT logoutSucceeded();
            Q_EMIT loggedInChanged();
        },
        Qt::QueuedConnection);
}

bool AuthService::isLoggedIn() const
{
    return m_loggedIn;
}

const User &AuthService::currentUserData() const
{
    return m_currentUser;
}

UserWrapper *AuthService::currentUser() const
{
    return m_currentUserWrapper;
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
            updateCurrentUser(std::move(user));
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

void AuthService::updateCurrentUser(User &&user)
{
    if (m_currentUser == user)
        return;
    m_currentUser.profile = user.profile;
    m_currentUser.prizes = user.prizes;
    m_currentUser.gu = user.gu;
    m_currentUser.eloHistory = user.eloHistory;
    m_currentUser.dailyCounts = user.dailyCounts;
    m_currentUserWrapper->setUser(m_currentUser);
    Q_EMIT currentUserChanged();
}
