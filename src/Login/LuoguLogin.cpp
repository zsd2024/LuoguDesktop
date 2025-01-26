#include "LuoguLogin.h"

LuoguLogin::LuoguLogin()
{
	std::random_device rd;
	std::mt19937 gen(rd());
}

LuoguLogin::~LuoguLogin()
{
}

QJsonObject LuoguLogin::operator()(QString username, QString password, QString captcha)
{
	return login(username, password, captcha);
}

QPixmap LuoguLogin::get_captcha()
{
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/lg4/captcha"));
	request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/login");
	request.setRawHeader("x-luogu-type", "content-only");
	QNetworkReply *response = manager.get(request);
	QByteArray byte_data = response->readAll();
	QPixmap captcha;
	captcha.loadFromData(byte_data);
	return captcha;
}

QJsonObject LuoguLogin::getCsrfToken()
{
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/"));
	request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/");
	request.setRawHeader("x-luogu-type", "content-only");
	QNetworkReply *getCsrfToken_reply = manager.get(request);
	if (getCsrfToken_reply != nullptr)
		getCsrfToken_reply->deleteLater();
	QObject::connect(&manager, &QNetworkAccessManager::finished, this, &LuoguLogin::getCsrfToken_finished);
	QEventLoop loop;
	QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	return {{"csrf-token", csrf_token}};
}

void LuoguLogin::getCsrfToken_finished(QNetworkReply *reply)
{
	qDebug() << "getCsrfToken: finished";
	QByteArray byte_text = reply->readAll();
	QString text(byte_text);
	qDebug() << "reply: " << text << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
	{
		QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
		qDebug() << "redirectUrl: " << redirectUrl;

		QNetworkRequest request(redirectUrl);
		request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
		request.setRawHeader("referer", "https://www.luogu.com.cn/");
		request.setRawHeader("x-luogu-type", "content-only");
		QNetworkReply *getCsrfToken_reply = manager.get(request);
		if (getCsrfToken_reply != nullptr)
			getCsrfToken_reply->deleteLater();
		QObject::connect(&manager, &QNetworkAccessManager::finished, this, &LuoguLogin::getCsrfToken_finished);
		QEventLoop loop;
		QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		loop.exec();
	}
	else if (text != "")
	{
		csrf_token = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
		qDebug() << "csrf-token: " << csrf_token;
	}
}

QJsonObject LuoguLogin::login(QString username, QString password, QString captcha)
{
	QJsonObject csrf_token = getCsrfToken();
	qDebug() << csrf_token;
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/login"));
	request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/login");
	request.setRawHeader("x-luogu-type", "content-only");
	request.setRawHeader("csrf-token", csrf_token["csrf-token"].toString().toUtf8());
	QNetworkReply *response = manager.post(request, QJsonDocument({{"username", username},
																   {"password", password},
																   {"captcha", captcha}})
														.toJson());
	QByteArray byte_text = response->readAll();
	QString text(byte_text);
	if (response->error() != QNetworkReply::NoError)
	{
		return {
			{"error", response->errorString()}};
	}
	return QJsonDocument::fromJson(text.toUtf8()).object();
}