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
				show(); });
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
			{ if(auth->logout())
				qApp->exit();
			else if (QMessageBox::critical(this, "登出失败", "登出失败，是否直接关闭 LuoguDesktop？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
					qApp->exit(); });
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
	main_layout->setSpacing(20);
	main_layout->setContentsMargins(20, 20, 20, 20);
	v_layout_1 = new QVBoxLayout();
	v_layout_2 = new QVBoxLayout();
	main_layout->addLayout(v_layout_1);
	main_layout->addLayout(v_layout_2);
	QColor backgroundColor = QColor(255, 255, 255, 150);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
		backgroundColor = QColor(50, 50, 50, 150); // 深色模式下使用更暗的背景色
#endif
	rounded_widget_1 = new RoundedWidget(this->centralWidget(), backgroundColor);
	rounded_widget_2 = new RoundedWidget(this->centralWidget(), backgroundColor);
	v_layout_1->addWidget(rounded_widget_1);
	v_layout_2->addWidget(rounded_widget_2);
	v_layout_1_1 = new QVBoxLayout(rounded_widget_1);
	v_layout_1_2 = new QVBoxLayout(rounded_widget_2);
	QString user_color_text = auth->user_info(auth->get_uid())["currentData"].toObject()["user"].toObject()["rating"].toObject()["user"].toObject()["color"].toString();
	QString user_color;
	if (user_color_text == "Gray")
		user_color = "#BFBFBF";
	else if (user_color_text == "Blue")
		user_color = "#3498DB";
	else if (user_color_text == "Green")
		user_color = "#52C41A";
	else if (user_color_text == "Orange")
		user_color = "#F39C11";
	else if (user_color_text == "Red")
		user_color = "#FE4C61";
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark) // 暗色颜色来自 Dark Reader
	{
		if (user_color_text == "Gray")
			user_color = "#C0BAB2";
		else if (user_color_text == "Blue")
			user_color = "#46A1DE";
		else if (user_color_text == "Green")
			user_color = "#7DE749";
		else if (user_color_text == "Orange")
			user_color = "#F4A628";
		else if (user_color_text == "Red")
			user_color = "#FE4F64";
	}
#endif
	greet_username = new QLabel(rounded_widget_1);
	QString safeUsername = auth->get_username().toHtmlEscaped(); // 转义特殊字符
	QString coloredText = "<span style='color:" + user_color + ";'>" + safeUsername + "</span>，";
	greet_username->setText(coloredText);
	greet_username->setTextFormat(Qt::RichText);
	QFont font_greet_username;
	font_greet_username.setPointSize(32);
	greet_username->setFont(font_greet_username);
	v_layout_1_1->addWidget(greet_username);

	greet = new QLabel(rounded_widget_1);
	qDebug() << auth->get_username();
	greet->setText("欢迎使用 LuoguDesktop！");
	QFont font_greet;
	font_greet.setPointSize(24);
	greet->setFont(font_greet);
	v_layout_1_1->addWidget(greet);

	h_layout_1_1_2 = new QHBoxLayout(nullptr);
	v_layout_1_1->addLayout(h_layout_1_1_2);

	rounded_widget_1_1_1_1 = new RoundedWidget(rounded_widget_1, backgroundColor);
	v_layout_1_1_1_1 = new QVBoxLayout(rounded_widget_1_1_1_1);
	h_layout_1_1_2->addWidget(rounded_widget_1_1_1_1);

	passed_problem_num_text = new QLabel(rounded_widget_1);
	passed_problem_num_text->setText("累计通过题目");
	QFont font_passed_problem_num_text;
	font_passed_problem_num_text.setPointSize(16);
	passed_problem_num_text->setFont(font_passed_problem_num_text);
	v_layout_1_1_1_1->addWidget(passed_problem_num_text, 0, Qt::AlignCenter);

	int passed_problem_num = auth->user_info(auth->get_uid())["currentData"].toObject()["passedProblems"].toArray().size();
	passed_problem_num_num = new QLabel(rounded_widget_1);
	passed_problem_num_num->setText(QString::fromStdString(std::to_string(passed_problem_num)) + "<span style='font-size:10px;'>道</span>");
	passed_problem_num_num->setTextFormat(Qt::RichText);
	QFont font_passed_problem_num_num;
	font_passed_problem_num_num.setPointSize(20);
	passed_problem_num_num->setFont(font_passed_problem_num_num);
	v_layout_1_1_1_1->addWidget(passed_problem_num_num, 0, Qt::AlignCenter);

	rounded_widget_1_1_1_2 = new RoundedWidget(rounded_widget_1, backgroundColor);
	v_layout_1_1_1_2 = new QVBoxLayout(rounded_widget_1_1_1_2);
	h_layout_1_1_2->addWidget(rounded_widget_1_1_1_2);

	matches_num_text = new QLabel(rounded_widget_1);
	matches_num_text->setText("累计参加 Rated 比赛");
	QFont font_matches_num_text;
	font_matches_num_text.setPointSize(16);
	matches_num_text->setFont(font_matches_num_text);
	v_layout_1_1_1_2->addWidget(matches_num_text, 0, Qt::AlignCenter);

	int matches_num = auth->elo_info(auth->get_uid())["count"].toInt();
	matches_num_num = new QLabel(rounded_widget_1);
	matches_num_num->setText(QString::fromStdString(std::to_string(matches_num)) + "<span style='font-size:10px;'>场</span>");
	matches_num_num->setTextFormat(Qt::RichText);
	QFont font_matches_num_num;
	font_matches_num_num.setPointSize(20);
	matches_num_num->setFont(font_matches_num_num);
	v_layout_1_1_1_2->addWidget(matches_num_num, 0, Qt::AlignCenter);

	v_layout_1_1_v_spacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
	v_layout_1_1->addItem(v_layout_1_1_v_spacer);

	if (config->getAutoPunch())
		if (!auth->punch())
			QMessageBox::critical(this, "打卡失败", "打卡失败！\n错误信息：" + auth->punch_info());
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
			else if (QMessageBox::critical(this, "登出失败", "登出失败，是否直接关闭 LuoguDesktop？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
				qApp->exit(); });
	connect(ui->about, &QAction::triggered, [this]
			{ QMessageBox::about(this, tr("关于 LuoguDesktop"), tr("<b>版本：</b>0.1 测试版<br><b>开发者：</b>zsd2024<br><b>GitHub：</b><a href='https://github.com/zsd2024/LuoguDesktop'>zsd2024/LuoguDesktop</a><center><font color='#808080'>Copyright (C) 2025 zsd2024. </font></center>")); });
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