#pragma once
#include "ui_LuoguDesktop.h"
#include "Auth/LuoguAuth.h"
#include "Config/Config.h"
#include "GetBackground/GetBackground.h"
#include "Login/Login.h"
#include "RoundedWidget/RoundedWidget.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyleHints>

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
    GetBackground *get_background;
    QPixmap background;
    QHBoxLayout *main_layout;
    QVBoxLayout *v_layout_1, *v_layout_2;
    QVBoxLayout *v_layout_1_1, *v_layout_1_2;
    QSpacerItem *v_layout_1_1_v_spacer;
    QLabel *greet_username, *greet;
    RoundedWidget *rounded_widget_1, *rounded_widget_2;
    bool is_first_close;
    void closeEvent(QCloseEvent *event) override;
    void setMenuAction();
    void setupSystemTray();
    void setupMainUI();
    std::shared_ptr<LuoguAuth> auth;
    Config *config;
    void paintEvent(QPaintEvent *event) override;
};