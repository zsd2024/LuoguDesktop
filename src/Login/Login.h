#pragma once
#include "ui_Login.h"
#include "LuoguLogin.h"
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

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
	void closeEvent(QCloseEvent *) override;

private:
	Ui_LoginWindow *ui;
	LuoguLogin login;
	QJsonObject cookie;
	void on_LoginButton_clicked();
	void on_captcha_image_clicked();
	bool succeed;

signals:
	void LoginSucceed();
};