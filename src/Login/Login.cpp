#include "Login.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui_LoginWindow)
{
	ui->setupUi(this);
	connect(ui->captcha_image, &QPushButton::clicked, [this]()
			{ on_captcha_image_clicked(); });
	connect(ui->LoginButton, &QPushButton::clicked, [this]()
			{ on_LoginButton_clicked(); });

	connect(ui->username_lineEdit, &QLineEdit::returnPressed, [this]()
			{ ui->password_lineEdit->setFocus(); });
	connect(ui->password_lineEdit, &QLineEdit::returnPressed, [this]()
			{ ui->captcha_lineEdit->setFocus(); });
	connect(ui->captcha_lineEdit, &QLineEdit::returnPressed, [this]()
			{ on_LoginButton_clicked(); });
	ui->captcha_lineEdit->installEventFilter(this);
	succeed = false;
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::closeEvent(QCloseEvent* event)
{
	if (succeed)
	{
		event->accept();
		return;
	}
	QMessageBox::StandardButton reply = QMessageBox::warning(this, "关闭确认", "登录未完成，确定关闭？", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		event->accept();
	} else {
		event->ignore();
	}
}

bool LoginWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui->captcha_lineEdit && event->type() == QEvent::FocusIn)
		on_captcha_image_clicked();
	return QWidget::eventFilter(obj, event);
}

void LoginWindow::on_LoginButton_clicked()
{
	try
	{
		QJsonObject res = login(ui->username_lineEdit->text(), ui->password_lineEdit->text(), ui->captcha_lineEdit->text());
		if (res.contains("error"))
		{
			// 弹出错误弹窗
			QMessageBox::critical(this, "登录失败", res["error"].toString());
			on_captcha_image_clicked();
			succeed = false;
		}
		else
		{
			QMessageBox::information(this, "登录成功", "欢迎回来，" + res["username"].toString() + "!");
			cookie = res["cookie"].toObject();
			qDebug() << cookie;
			succeed = true;
			emit LoginSucceed();
			close();
		}
	}
	catch (const std::exception &e)
	{
		// 弹出错误弹窗
		QMessageBox::critical(this, "登录失败", e.what());
	}
}

void LoginWindow::on_captcha_image_clicked()
{
	QPixmap pixmap = QPixmap(login.get_captcha());
	ui->captcha_image->setIcon(pixmap);
	ui->captcha_image->setIconSize(pixmap.size());
}