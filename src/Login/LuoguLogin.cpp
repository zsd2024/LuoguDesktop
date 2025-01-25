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
	QNetworkAccessManager manager;
	return login(username, password, captcha, manager);
}

QPixmap LuoguLogin::get_captcha()
{
	QNetworkAccessManager manager;
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

QJsonObject LuoguLogin::getCsrfToken(QNetworkAccessManager &manager)
{
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/"));
	// request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	// request.setRawHeader("referer", "https://www.luogu.com.cn/");
	// request.setRawHeader("x-luogu-type", "content-only");
	QNetworkReply *response = manager.get(request);
	QByteArray byte_text = response->readAll();
	QString text(byte_text);
	qDebug() << text;
	qDebug() << "getCsrfToken: error" << response->errorString();
	qDebug() << "getCsrfToken: error code" << response->error();
	qDebug() << "getCsrfToken: attribute" << response->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (response->error() != QNetworkReply::NoError)
	{
		throw std::runtime_error(response->errorString().toStdString());
	}
	if (text == "")
	{
		throw std::runtime_error("getCsrfToken: empty text");
	}
	QString csrf_token_text = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
	return {
		{"csrf-token", csrf_token_text}};
}

QJsonObject LuoguLogin::login(QString username, QString password, QString captcha, QNetworkAccessManager &manager)
{
	QJsonObject csrf_token = getCsrfToken(manager);
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