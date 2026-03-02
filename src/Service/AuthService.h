#pragma once

#include "ModelViews/UserWrapper.h"
#include "Repository/AuthRepository.h"
#include "Repository/UserRepository.h"
#include <QImage>

class AuthService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isLoggedIn READ isLoggedIn NOTIFY loggedInChanged)
    Q_PROPERTY(UserWrapper *currentUser READ currentUser NOTIFY currentUserChanged)
    Q_PROPERTY(bool buzyLogin READ buzyLogin NOTIFY buzyLoginChanged)
    Q_PROPERTY(bool buzyCaptcha READ buzyCaptcha NOTIFY buzyCaptchaChanged)

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

    // 当前登录用户数据（非响应式）
    const User &currentUserData() const;

    // 当前登录用户（响应式包装器）
    UserWrapper *currentUser() const;

    // 当前登录忙碌状态
    bool buzyLogin() const;

    // 当前验证码忙碌状态
    bool buzyCaptcha() const;

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
    void captchaRefreshed(const QString &captcha);
    // 登录忙碌状态改变
    void buzyLoginChanged();
    // 验证码忙碌状态改变
    void buzyCaptchaChanged();

private:
    AuthRepository *m_authRepo;
    UserRepository *m_userRepo;

    bool m_loggedIn = false;
    User m_currentUser;
    UserWrapper *m_currentUserWrapper;

    bool m_buzyLogin = false;
    bool m_buzyCaptcha = false;

    void updateCurrentUser(User &&user);
};
