#include "LuoguLogin.h"

LuoguLogin::LuoguLogin()
{
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
	request.setRawHeader("user-agent", "");
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
	request.setRawHeader("user-agent", "");
	request.setRawHeader("referer", "https://www.luogu.com.cn/");
	request.setRawHeader("x-luogu-type", "content-only");
	QNetworkReply *response = manager.get(request);
	QByteArray byte_text = response->readAll();
	QString text(byte_text);
	QString csrf_token_text = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
	return {
		{"csrf-token", csrf_token_text}};
}

QJsonObject LuoguLogin::login(QString username, QString password, QString captcha, QNetworkAccessManager &manager)
{
	QJsonObject csrf_token = getCsrfToken(manager);
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/login"));
	request.setRawHeader("user-agent", "");
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