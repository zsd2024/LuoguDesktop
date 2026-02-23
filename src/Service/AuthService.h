#pragma once

#include "Repository/AuthRepository.h"
#include "Repository/UserRepository.h"
#include <QImage>

class AuthService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool loggedIn READ isLoggedIn NOTIFY loggedInChanged)
    Q_PROPERTY(User currentUser READ currentUser NOTIFY currentUserChanged)

public:
    explicit AuthService(AuthRepository *authRepo, UserRepository *userRepo, QObject *parent = nullptr);

    // ===== 登录登出 =====

    // 登录
    Q_INVOKABLE void login(const QString &username, const QString &password, const QString &captcha);

    // 登出
    Q_INVOKABLE void logout();

    // ===== 状态查询 =====

    // 是否已登录
    bool isLoggedIn() const;

    // 当前登录用户
    const User &currentUser() const;

    // 重新获取用户信息
    Q_INVOKABLE void refreshCurrentUser();

    // 刷新验证码
    Q_INVOKABLE void refreshCaptcha();

Q_SIGNALS:
    // 登录成功
    void loginSucceeded();
    // 登录失败
    void loginFailed(const QString &reason);
    // 登录状态改变
    void loggedInChanged();
    // 当前用户改变
    void currentUserChanged();
    // 登出成功
    void logoutSucceeded();
    // 验证码刷新成功
    void captchaRefreshed(const QImage &captcha);

private:
    AuthRepository *m_authRepo;
    UserRepository *m_userRepo;

    bool m_loggedIn = false;
    User m_currentUser;
};
