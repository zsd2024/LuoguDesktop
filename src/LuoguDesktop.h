#pragma once
#include "ui_LuoguDesktop.h"
#include "Auth/LuoguAuth.h"
#include "Config/Config.h"
#include "GetBackground/GetBackground.h"
#include "Login/Login.h"
#include "RoundedWidget/RoundedWidget.h"
#include "Common/Common.h"
#include "Discuss/Discuss.h"
#include "Contest/Contest.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyleHints>
#include <QListWidget>

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
    QVBoxLayout *v_layout_1_1, *v_layout_1_2, *v_layout_2_1, *v_layout_2_2;
    QHBoxLayout *h_layout_1_1_2;
    RoundedWidget *rounded_widget_1_1_1_1;
    QVBoxLayout *v_layout_1_1_1_1;
    RoundedWidget *rounded_widget_1_1_1_2;
    QVBoxLayout *v_layout_1_1_1_2;
    QSpacerItem *v_layout_1_1_v_spacer;
    QLabel *greet_username, *greet;
    QLabel *passed_problem_num_text, *passed_problem_num_num;
    QLabel *matches_num_text, *matches_num_num;
    RoundedWidget *rounded_widget_1_1, *rounded_widget_1_2;
    RoundedWidget *rounded_widget_2_1, *rounded_widget_2_2;
    QListWidget *discuss_list;
    QVector<std::shared_ptr<QListWidgetItem>> discuss_list_widget_items;
    QVector<std::shared_ptr<RoundedWidget>> discuss_rounded_widgets;
    QVector<std::shared_ptr<QVBoxLayout>> discuss_layouts;
    QVector<std::shared_ptr<QLabel>> discuss_labels;
    QListWidget *submitted_problem_list;
    QVector<std::shared_ptr<QListWidgetItem>> submitted_problem_list_widget_items;
    QVector<std::shared_ptr<RoundedWidget>> submitted_problem_rounded_widgets;
    QVector<std::shared_ptr<QVBoxLayout>> submitted_problem_layouts;
    QVector<std::shared_ptr<QLabel>> submitted_problem_labels;
    QListWidget *contests_list;
    QVector<std::shared_ptr<QListWidgetItem>> contests_list_widget_items;
    QVector<std::shared_ptr<RoundedWidget>> contests_rounded_widgets;
    QVector<std::shared_ptr<QVBoxLayout>> contests_layouts;
    QVector<std::shared_ptr<QLabel>> contests_labels;
    bool is_first_close;
    void closeEvent(QCloseEvent *event) override;
    void setMenuAction();
    void setupSystemTray();
    void setupMainUI();
    std::shared_ptr<LuoguAuth> auth;
    Config *config;
    Discuss *discuss;
    Contest *contest;
    void paintEvent(QPaintEvent *event) override;
};