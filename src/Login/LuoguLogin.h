#ifndef LUOGULOGIN_H
#define LUOGULOGIN_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
class LuoguLogin
{
public:
	LuoguLogin();
	~LuoguLogin();
	QJsonObject operator()(QString username, QString password, QString captcha);
	QPixmap get_captcha();

private:
	QJsonObject getCsrfToken(QNetworkAccessManager &manager);
	QJsonObject login(QString username, QString password, QString captcha, QNetworkAccessManager &manager);
};

#endif // LUOGULOGIN_H