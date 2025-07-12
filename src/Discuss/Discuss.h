#ifndef DISCUSS_H
#define DISCUSS_H
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include "../Common/Common.h"
class Discuss : public QObject
{
	Q_OBJECT
public:
	Discuss();
	~Discuss();
	QJsonArray getDiscusses();
};
#endif