#include "LuoguDesktop.h"

LuoguDesktop::LuoguDesktop(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_LuoguDesktop), login(new LoginWindow)
{
    ui->setupUi(this);
    this->hide();
    is_first_close = true;
    connect(login, &LoginWindow::LoginSucceed, [this]()
            {
                setupSystemTray();
                SysTray->show();
                setupMainUI();
                show();
                qDebug() << config->getAutoPunch(); });
    setMenuAction();
    auth = login->get_auth();
    login->start();
}

void LuoguDesktop::setupSystemTray()
{
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
}

void LuoguDesktop::setupMainUI()
{
    config = new Config();
    get_background = new GetBackground();
    background = (*get_background)();
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(background));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    main_layout = new QHBoxLayout(this->centralWidget());
    v_layout_1 = new QVBoxLayout();
    v_layout_2 = new QVBoxLayout();
    main_layout->addLayout(v_layout_1);
    main_layout->addLayout(v_layout_2);
    QColor backgroundColor = QColor(255, 255, 255, 220);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
        backgroundColor = QColor(50, 50, 50, 220); // 深色模式下使用更暗的背景色
#endif
    blur_widget_1 = new RoundedBlurWidget(this->centralWidget(), backgroundColor);
    blur_widget_2 = new RoundedBlurWidget(this->centralWidget(), backgroundColor);
    v_layout_1->addWidget(blur_widget_1);
    v_layout_2->addWidget(blur_widget_2);
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
    delete get_background;
    delete main_layout;
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

void LuoguDesktop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaled = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    // 计算居中显示的偏移
    int x = (scaled.width() - width()) / 2;
    int y = (scaled.height() - height()) / 2;
    painter.drawPixmap(0, 0, scaled, x, y, width(), height());
    QMainWindow::paintEvent(event);
}