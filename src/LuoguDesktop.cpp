#include "LuoguDesktop.h"

LuoguDesktop::LuoguDesktop(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_LuoguDesktop), login(new LoginWindow)
{
    ui->setupUi(this);
    this->hide();
    SysTray = new QSystemTrayIcon(this);
    SysTray->setIcon(QIcon(":/images/assets/logo.svg"));
    SysTray->setToolTip("LuoguDesktop");
    quit_action = new QAction("退出", this);
    connect(quit_action, &QAction::triggered, [this]()
            { auth->logout();
                qApp->quit(); });
    show_action = new QAction("显示", this);
    connect(show_action, &QAction::triggered, [this]()
            { show(); });
    connect(SysTray, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason)
            {switch (reason)
        {
        case QSystemTrayIcon::Trigger:
            show();
            break;
        default:
            break;
        } });
    SysTrayMenu = new QMenu(this);
    SysTrayMenu->addAction(show_action);
    SysTrayMenu->addSeparator();
    SysTrayMenu->addAction(quit_action);
    SysTray->setContextMenu(SysTrayMenu);
    SysTray->show();
    is_first_close = true;
    connect(login, &LoginWindow::LoginSucceed, [this]()
            { show();
        qDebug() << config->getAutoPunch();});
    setMenuAction();
    auth = login->get_auth();
    config = new Config();
    login->show();
}

LuoguDesktop::~LuoguDesktop()
{
    delete ui;
    delete login;
    delete SysTray;
    delete SysTrayMenu;
    delete show_action;
    delete quit_action;
    delete config;
}

void LuoguDesktop::setMenuAction()
{
    connect(ui->exit, &QAction::triggered, [this]
            { if(auth->logout())
                qApp->exit();
            else
            {
            if (QMessageBox::critical(this, "登出失败", "登出失败，是否直接关闭 LuoguDesktop？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
            {
                qApp->exit();
            }} });
}

void LuoguDesktop::closeEvent(QCloseEvent *event)
{
    if (SysTray->isVisible())
    {
        hide();
        if (is_first_close)
        {
            SysTray->showMessage("提示", "窗口已最小化至托盘");
            is_first_close = false;
        }
        event->ignore();
    }
    else
        event->accept();
}