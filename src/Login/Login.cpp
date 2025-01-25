#include "Login.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui_LoginWindow)
{
	ui->setupUi(this);
	ui->captcha_image->setPixmap(login.get_captcha());
	connect(ui->LoginButton, &QPushButton::clicked, this, &LoginWindow::on_LoginButton_clicked);
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
	LuoguLogin login;
	QJsonObject res = login(ui->username_lineEdit->text(), ui->password_lineEdit->text(), ui->captcha_lineEdit->text());
	if (res.contains("error"))
	{
		// 弹出错误弹窗
		QMessageBox::critical(this, "登录失败", res["error"].toString());
		ui->captcha_image->setPixmap(login.get_captcha());
	}
}