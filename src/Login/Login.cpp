#include "Login.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui_LoginWindow)
{
	ui->setupUi(this);
	connect(ui->captcha_image, &QPushButton::clicked, this, &LoginWindow::on_captcha_image_clicked);
	connect(ui->LoginButton, &QPushButton::clicked, this, &LoginWindow::on_LoginButton_clicked);
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
	LuoguLogin login;
	try
	{
		QJsonObject res = login(ui->username_lineEdit->text(), ui->password_lineEdit->text(), ui->captcha_lineEdit->text());
		if (res.contains("error"))
		{
			// 弹出错误弹窗
			QMessageBox::critical(this, "登录失败", res["error"].toString());
			on_captcha_image_clicked();
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