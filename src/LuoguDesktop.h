#pragma once
#include "ui_LuoguDesktop.h"
#include "Login/Login.h"
#include "Auth/LuoguAuth.h"
#include "Config/Config.h"
#include <QMainWindow>
#include <QSystemTrayIcon>

class LuoguDesktop : public QMainWindow
{
    Q_OBJECT

public:
    LuoguDesktop(QWidget *parent = nullptr);
    ~LuoguDesktop();

private:
    Ui_LuoguDesktop *ui;
    LoginWindow *login;
    QSystemTrayIcon *SysTray;
    QAction *show_action;
    QAction *quit_action;
    QMenu *SysTrayMenu;
    bool is_first_close;
    void closeEvent(QCloseEvent *event) override;
    void setMenuAction();
    std::shared_ptr<LuoguAuth> auth;
    Config *config;
};