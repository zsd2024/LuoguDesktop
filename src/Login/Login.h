#pragma once
#include "ui_Login.h"
#include "LuoguLogin.h"
#include <QWidget>
#include <QJsonObject>
#include <QMessageBox>

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();

private:
	Ui_LoginWindow *ui;
	LuoguLogin login;
	void on_LoginButton_clicked();
	void on_captcha_image_clicked();
};