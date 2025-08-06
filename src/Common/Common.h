#ifndef COMMON_H
#define COMMON_H
#include <QObject>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
class Common : public QObject
{
	Q_OBJECT
public:
	Common();
	~Common();
	static void init();
	static void destroy();
	static Poco::Net::HTTPSClientSession *client;
	static Poco::Net::NameValueCollection cookie;
	static std::string getUserAgent();
	static QJsonObject getCsrfToken();

private:
	static Poco::Net::Context *pCtx;
	static QString csrf_token;
	static QString C3VK;
};
#endif