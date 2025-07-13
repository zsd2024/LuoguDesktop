#ifndef CONTEST_H
#define CONTEST_H
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include "../Common/Common.h"
class Contest : public QObject
{
	Q_OBJECT
public:
	Contest();
	~Contest();
	QJsonArray getContests();
};
#endif