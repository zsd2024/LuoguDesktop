#pragma once
#include "ui_Login.h"
#include "../Auth/LuoguAuth.h"
#include <QWidget>
#include <QJsonObject>
#include <QMessageBox>
#include <QCloseEvent>

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
	std::shared_ptr<LuoguAuth> get_auth();
	void start();

protected:
	void closeEvent(QCloseEvent *) override;

private:
	Ui_LoginWindow *ui;
	std::shared_ptr<LuoguAuth> auth;
	QJsonObject cookie;
	void on_LoginButton_clicked();
	void on_captcha_image_clicked();
	bool succeed;

signals:
	void LoginSucceed();
};