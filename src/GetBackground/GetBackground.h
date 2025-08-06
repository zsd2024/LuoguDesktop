#ifndef GETBACKGROUND_H
#define GETBACKGROUND_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QPixmap>
#include <QVector>
#include <QString>
// #include <QNetworkAccessManager>
// #include <QNetworkCookieJar>
// #include <QNetworkCookie>
// #include <QNetworkProxy>
// #include <QNetworkReply>
// #include <QNetworkRequest>
#include <QDebug>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <random>
class GetBackground : public QObject
{
	Q_OBJECT
public:
	GetBackground();
	~GetBackground();
	QPixmap operator()();

private:
	const QString User_Agent =
#ifdef _WIN32
#ifdef _WIN64
		"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36";
#else
		"Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.94 Safari/537.36";
#endif
#else
#ifdef __linux__
		"Mozilla/5.0 (X11; Linux x86_64; rv:140.0) Gecko/20100101 Firefox/140.0";
#else
		"Mozilla/5.0 (Linux; Android 4.0.4; Galaxy Nexus Build/IMM76B) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.133 Mobile Safari/535.19";
#endif
#endif
	Poco::Net::HTTPSClientSession *client;
	Poco::Net::NameValueCollection cookie;
	QPixmap background;
	QByteArray getUserAgent();
	QPixmap get_background();
	QString get_background_url();
	Poco::Net::Context *pCtx;
};

#endif // GETBACKGROUND_H