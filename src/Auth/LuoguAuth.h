#ifndef LUOGUAUTH_H
#define LUOGUAUTH_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QPixmap>
#include <QVector>
#include <QString>
#include <QDebug>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <cstdlib>
#include <random>
#include "../Common/Common.h"
class LuoguAuth : public QObject
{
	Q_OBJECT
public:
	LuoguAuth();
	~LuoguAuth();
	QJsonObject operator()(QString username, QString password, QString captcha);
	QPixmap get_captcha();
	QJsonObject user_info(int uid, bool cache = true);
	QJsonObject elo_info(int uid, bool cache = true);
	bool punch();
	QString punch_info();
	bool logout();
	QString get_username();
	int get_uid();

private:
	QString username;
	QPixmap captcha;
	QString login_text;
	QJsonObject user_info_cache;
	QJsonObject elo_info_cache;
	QJsonObject login(QString username, QString password, QString captcha);
	QJsonObject get_elo_info_page(int uid, int page, int limit);
	Poco::Net::Context *pCtx;
	QString punch_info_cache;
};

#endif // LUOGUAUTH_H