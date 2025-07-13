#include "LuoguDesktop.h"

LuoguDesktop::LuoguDesktop(QWidget *parent)
	: QMainWindow(parent), ui(new Ui_LuoguDesktop), login(new LoginWindow)
{
	Common::init();
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
	config = new Config();
	get_background = new GetBackground();
	discuss = new Discuss();
	contest = new Contest();
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

	delete v_layout_1;
	delete v_layout_2;
	delete v_layout_1_1;
	delete v_layout_2_1;
	delete h_layout_1_1_2;

	delete rounded_widget_1_1_1_1;
	delete v_layout_1_1_1_1;
	delete rounded_widget_1_1_1_2;
	delete v_layout_1_1_1_2;

	delete v_layout_1_1_v_spacer;

	delete greet_username;
	delete greet;

	delete passed_problem_num_text;
	delete passed_problem_num_num;
	delete matches_num_text;
	delete matches_num_num;

	delete rounded_widget_1_1;
	delete rounded_widget_2_1;

	delete discuss_list;
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
	rounded_widget_1_1 = new RoundedWidget(this->centralWidget(), backgroundColor);
	rounded_widget_1_2 = new RoundedWidget(this->centralWidget(), backgroundColor);
	rounded_widget_2_1 = new RoundedWidget(this->centralWidget(), backgroundColor);
	rounded_widget_2_2 = new RoundedWidget(this->centralWidget(), backgroundColor);
	v_layout_1->addWidget(rounded_widget_1_1);
	v_layout_1->addWidget(rounded_widget_1_2);
	v_layout_2->addWidget(rounded_widget_2_1);
	v_layout_2->addWidget(rounded_widget_2_2);
	v_layout_1_1 = new QVBoxLayout(rounded_widget_1_1);
	v_layout_1_2 = new QVBoxLayout(rounded_widget_1_2);
	v_layout_2_1 = new QVBoxLayout(rounded_widget_2_1);
	v_layout_2_2 = new QVBoxLayout(rounded_widget_2_2);
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
	greet_username = new QLabel(rounded_widget_1_1);
	QString safeUsername = auth->get_username().toHtmlEscaped(); // 转义特殊字符
	QString coloredText = "<span style='color:" + user_color + ";'>" + safeUsername + "</span>，";
	greet_username->setText(coloredText);
	greet_username->setTextFormat(Qt::RichText);
	QFont font_greet_username;
	font_greet_username.setPointSize(32);
	greet_username->setFont(font_greet_username);
	v_layout_1_1->addWidget(greet_username);

	greet = new QLabel(rounded_widget_1_1);
	qDebug() << auth->get_username();
	greet->setText("欢迎使用 LuoguDesktop！");
	QFont font_greet;
	font_greet.setPointSize(24);
	greet->setFont(font_greet);
	v_layout_1_1->addWidget(greet);

	h_layout_1_1_2 = new QHBoxLayout(nullptr);
	v_layout_1_1->addLayout(h_layout_1_1_2);

	rounded_widget_1_1_1_1 = new RoundedWidget(rounded_widget_1_1, backgroundColor);
	v_layout_1_1_1_1 = new QVBoxLayout(rounded_widget_1_1_1_1);
	h_layout_1_1_2->addWidget(rounded_widget_1_1_1_1);

	passed_problem_num_text = new QLabel(rounded_widget_1_1);
	passed_problem_num_text->setText("累计通过题目");
	QFont font_passed_problem_num_text;
	font_passed_problem_num_text.setPointSize(16);
	passed_problem_num_text->setFont(font_passed_problem_num_text);
	v_layout_1_1_1_1->addWidget(passed_problem_num_text, 0, Qt::AlignCenter);

	qDebug() << auth->user_info(auth->get_uid())["currentData"].toObject();

	int passed_problem_num = auth->user_info(auth->get_uid())["currentData"].toObject()["passedProblems"].toArray().size();
	passed_problem_num_num = new QLabel(rounded_widget_1_1);
	passed_problem_num_num->setText(QString::fromStdString(std::to_string(passed_problem_num)) + "<span style='font-size:10px;'>道</span>");
	passed_problem_num_num->setTextFormat(Qt::RichText);
	QFont font_passed_problem_num_num;
	font_passed_problem_num_num.setPointSize(20);
	passed_problem_num_num->setFont(font_passed_problem_num_num);
	v_layout_1_1_1_1->addWidget(passed_problem_num_num, 0, Qt::AlignCenter);

	rounded_widget_1_1_1_2 = new RoundedWidget(rounded_widget_1_1, backgroundColor);
	v_layout_1_1_1_2 = new QVBoxLayout(rounded_widget_1_1_1_2);
	h_layout_1_1_2->addWidget(rounded_widget_1_1_1_2);

	matches_num_text = new QLabel(rounded_widget_1_1);
	matches_num_text->setText("累计参加 Rated 比赛");
	QFont font_matches_num_text;
	font_matches_num_text.setPointSize(16);
	matches_num_text->setFont(font_matches_num_text);
	v_layout_1_1_1_2->addWidget(matches_num_text, 0, Qt::AlignCenter);

	int matches_num = auth->elo_info(auth->get_uid())["count"].toInt();
	matches_num_num = new QLabel(rounded_widget_1_1);
	matches_num_num->setText(QString::fromStdString(std::to_string(matches_num)) + "<span style='font-size:10px;'>场</span>");
	matches_num_num->setTextFormat(Qt::RichText);
	QFont font_matches_num_num;
	font_matches_num_num.setPointSize(20);
	matches_num_num->setFont(font_matches_num_num);
	v_layout_1_1_1_2->addWidget(matches_num_num, 0, Qt::AlignCenter);

	discuss_list = new QListWidget(centralWidget());
	discuss_list->setSelectionMode(QAbstractItemView::NoSelection);
	discuss_list->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	discuss_list->setStyleSheet("background-color: transparent;");
	discuss_list->setAttribute(Qt::WA_StyledBackground);
	discuss_list->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	QJsonArray discusses = discuss->getDiscusses();
	for (const QJsonValueConstRef item : discusses)
	{
		QJsonObject discuss_item = item.toObject();
		std::shared_ptr<QListWidgetItem> discuss_item_item = std::make_shared<QListWidgetItem>(discuss_list);
		discuss_list->addItem(discuss_item_item.get());
		std::shared_ptr<RoundedWidget> discuss_item_widget = std::make_shared<RoundedWidget>(discuss_list, backgroundColor);
		discuss_list->setItemWidget(discuss_item_item.get(), discuss_item_widget.get());
		std::shared_ptr<QLabel> discuss_item_label = std::make_shared<QLabel>(discuss_item_widget.get());
		discuss_item_label->setText(discuss_item["title"].toString());
		QFont font_discuss_item_label;
		font_discuss_item_label.setPointSize(10);
		discuss_item_label->setFont(font_discuss_item_label);
		std::shared_ptr<QVBoxLayout> discuss_item_layout = std::make_shared<QVBoxLayout>(discuss_item_widget.get());
		discuss_item_layout->addWidget(discuss_item_label.get());
		discuss_item_widget->resize(discuss_item_label->width(), discuss_item_label->height() + 15);
		discuss_item_item->setSizeHint(discuss_item_widget->size());
		discuss_list_widget_items.push_back(discuss_item_item);
		discuss_rounded_widgets.push_back(discuss_item_widget);
		discuss_layouts.push_back(discuss_item_layout);
		discuss_labels.push_back(discuss_item_label);
	}
	v_layout_1_2->addWidget(discuss_list);

	submitted_problem_list = new QListWidget(centralWidget());
	submitted_problem_list->setSelectionMode(QAbstractItemView::NoSelection);
	submitted_problem_list->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	submitted_problem_list->setStyleSheet("background-color: transparent;");
	submitted_problem_list->setAttribute(Qt::WA_StyledBackground);
	submitted_problem_list->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	QJsonArray submitted_problemes = auth->user_info(auth->get_uid())["currentData"].toObject()["submittedProblems"].toArray();
	for (const QJsonValueConstRef item : submitted_problemes)
	{
		QJsonObject submitted_problem_item = item.toObject();
		std::shared_ptr<QListWidgetItem> submitted_problem_item_item = std::make_shared<QListWidgetItem>(submitted_problem_list);
		submitted_problem_list->addItem(submitted_problem_item_item.get());
		std::shared_ptr<RoundedWidget> submitted_problem_item_widget = std::make_shared<RoundedWidget>(submitted_problem_list, backgroundColor);
		submitted_problem_list->setItemWidget(submitted_problem_item_item.get(), submitted_problem_item_widget.get());
		std::shared_ptr<QLabel> submitted_problem_item_label = std::make_shared<QLabel>(submitted_problem_item_widget.get());
		submitted_problem_item_label->setText(submitted_problem_item["pid"].toString() + " <b>" + submitted_problem_item["title"].toString().toHtmlEscaped() + "</b>");
		QFont font_submitted_problem_item_label;
		font_submitted_problem_item_label.setPointSize(10);
		submitted_problem_item_label->setFont(font_submitted_problem_item_label);
		std::shared_ptr<QVBoxLayout> submitted_problem_item_layout = std::make_shared<QVBoxLayout>(submitted_problem_item_widget.get());
		submitted_problem_item_layout->addWidget(submitted_problem_item_label.get());
		submitted_problem_item_widget->resize(submitted_problem_item_label->width(), submitted_problem_item_label->height() + 15);
		submitted_problem_item_item->setSizeHint(submitted_problem_item_widget->size());
		submitted_problem_list_widget_items.push_back(submitted_problem_item_item);
		submitted_problem_rounded_widgets.push_back(submitted_problem_item_widget);
		submitted_problem_layouts.push_back(submitted_problem_item_layout);
		submitted_problem_labels.push_back(submitted_problem_item_label);
	}
	v_layout_2_1->addWidget(submitted_problem_list);

	contests_list = new QListWidget(centralWidget());
	contests_list->setSelectionMode(QAbstractItemView::NoSelection);
	contests_list->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	contests_list->setStyleSheet("background-color: transparent;");
	contests_list->setAttribute(Qt::WA_StyledBackground);
	contests_list->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	QJsonArray contests = contest->getContests();
	qDebug() << contests;
	for (const QJsonValueConstRef item : contests)
	{
		QJsonObject contests_item = item.toObject();
		std::shared_ptr<QListWidgetItem> contests_item_item = std::make_shared<QListWidgetItem>(contests_list);
		contests_list->addItem(contests_item_item.get());
		std::shared_ptr<RoundedWidget> contests_item_widget = std::make_shared<RoundedWidget>(contests_list, backgroundColor);
		contests_list->setItemWidget(contests_item_item.get(), contests_item_widget.get());
		std::shared_ptr<QLabel> contests_item_label = std::make_shared<QLabel>(contests_item_widget.get());
		contests_item_label->setText(contests_item["name"].toString());
		QFont font_contests_item_label;
		font_contests_item_label.setPointSize(10);
		contests_item_label->setFont(font_contests_item_label);
		std::shared_ptr<QVBoxLayout> contests_item_layout = std::make_shared<QVBoxLayout>(contests_item_widget.get());
		contests_item_layout->addWidget(contests_item_label.get());
		contests_item_widget->resize(contests_item_label->width(), contests_item_label->height() + 15);
		contests_item_item->setSizeHint(contests_item_widget->size());
		contests_list_widget_items.push_back(contests_item_item);
		contests_rounded_widgets.push_back(contests_item_widget);
		contests_layouts.push_back(contests_item_layout);
		contests_labels.push_back(contests_item_label);
	}
	v_layout_2_2->addWidget(contests_list);

	// v_layout_1_1_v_spacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
	// v_layout_1_1->addItem(v_layout_1_1_v_spacer);

	if (config->getAutoPunch())
		if (!auth->punch())
			QMessageBox::critical(this, "打卡失败", "打卡失败！\n错误信息：" + auth->punch_info());
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