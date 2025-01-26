#ifndef LUOGULOGIN_H
#define LUOGULOGIN_H

#include <QByteArray>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QPixmap>
#include <QVector>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <random>
class LuoguLogin : public QObject
{
	Q_OBJECT
public:
	LuoguLogin();
	~LuoguLogin();
	QJsonObject operator()(QString username, QString password, QString captcha);
	QPixmap get_captcha();

private:
	const QVector<QString> User_Agent = {
		"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36",
		"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36",
		"Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/10.0.648.133 Safari/534.16",
		"Mozilla/5.0 (Linux; Android 4.0.4; Galaxy Nexus Build/IMM76B) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.133 Mobile Safari/535.19",
		"Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.94 Safari/537.36"};
	std::mt19937 gen;
	QNetworkAccessManager manager;
	QNetworkReply *getCsrfToken_reply = nullptr;
	QNetworkReply *login_reply = nullptr;
	QString csrf_token;
	QJsonObject getCsrfToken();
	void getCsrfToken_finished(QNetworkReply *reply);
	QJsonObject login(QString username, QString password, QString captcha);
};

#endif // LUOGULOGIN_H