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
	void on_LoginButton_clicked();

private:
	Ui_LoginWindow *ui;
	LuoguLogin login;
};