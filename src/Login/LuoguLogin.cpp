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
	QNetworkAccessManager manager;
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/lg4/captcha"));
	request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/");
	request.setRawHeader("x-luogu-type", "content-only");
	get_captcha_reply = manager.get(request);
	if (get_captcha_reply != nullptr)
		get_captcha_reply->deleteLater();
	QObject::connect(&manager, &QNetworkAccessManager::finished, this, &LuoguLogin::get_captcha_finished);
	QEventLoop loop;
	QObject::connect(get_captcha_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	return captcha;
}

void LuoguLogin::get_captcha_finished(QNetworkReply *reply)
{
	qDebug() << "getCsrfToken: finished";
	QByteArray byte_text = reply->readAll();
	// qDebug() << "reply: " << byte_text << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
	{
		QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
		qDebug() << "redirectUrl: " << redirectUrl;

		QNetworkRequest request(redirectUrl);
		request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
		request.setRawHeader("user-agent", User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
		request.setRawHeader("referer", "https://www.luogu.com.cn/");
		request.setRawHeader("x-luogu-type", "content-only");
		QNetworkReply *getCsrfToken_reply = manager.get(request);
		if (getCsrfToken_reply != nullptr)
			getCsrfToken_reply->deleteLater();
		QObject::connect(&manager, &QNetworkAccessManager::finished, this, &LuoguLogin::get_captcha_finished);
		QEventLoop loop;
		QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		loop.exec();
	}
	else if (byte_text != "")
	{
		captcha.loadFromData(byte_text);
		qDebug() << "captcha: " << captcha;
	}
}

QJsonObject LuoguLogin::getCsrfToken()
{
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/"));
	request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/");
	request.setRawHeader("x-luogu-type", "content-only");
	getCsrfToken_reply = manager.get(request);
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
	// qDebug() << "reply: " << text << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
	{
		QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
		qDebug() << "redirectUrl: " << redirectUrl;

		QNetworkRequest request(redirectUrl);
		request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
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
	else if (text != "" && text.contains("<meta name=\"csrf-token\" content=\""))
	{
		csrf_token = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
		qDebug() << "csrf-token: " << csrf_token;
		QList<QNetworkCookie> l = (manager.cookieJar()->cookiesForUrl(QUrl("https://www.luogu.com.cn/")));
		qDebug() << l[0].name() << l[0].value();
		qDebug() << l[1].name() << l[1].value();
		qDebug() << l[2].name() << l[2].value();
	}
}

QJsonObject LuoguLogin::login(QString username, QString password, QString captcha)
{
	QJsonObject csrf_token = getCsrfToken();
	qDebug() << csrf_token;
	QNetworkRequest request(QUrl("https://www.luogu.com.cn/do-auth/password"));
	request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	request.setRawHeader("referer", "https://www.luogu.com.cn/auth/login");
	request.setRawHeader("host", "www.luogu.com.cn");
	request.setRawHeader("origin", "https://www.luogu.com.cn");
	request.setRawHeader("x-luogu-type", "content-only");
	request.setRawHeader("x-csrf-token", csrf_token["csrf-token"].toString().toUtf8());
	request.setRawHeader("x-requested-with", "XMLHttpRequest");
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	qDebug() << QJsonDocument({{"username", username},
							   {"password", password},
							   {"captcha", captcha}})
					.toJson()
					.toStdString()
					.c_str();
	login_reply = manager.post(request, QJsonDocument({{"username", username},
													   {"password", password},
													   {"captcha", captcha}})
											.toJson());
	if (login_reply != nullptr)
		login_reply->deleteLater();
	QObject::connect(&manager, &QNetworkAccessManager::finished, this, &LuoguLogin::login_finished);
	QEventLoop loop;
	QObject::connect(login_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	return QJsonDocument::fromJson(login_text.toUtf8()).object();
}
void LuoguLogin::login_finished(QNetworkReply *reply)
{
	qDebug() << "login: finished";
	if (reply->error() != QNetworkReply::NoError)
	{
		login_text = QString(QJsonDocument({{"error", reply->errorString()}}).toJson());
	}
	else
	{
		QByteArray byte_text = reply->readAll();
		login_text = QString(byte_text);
		qDebug() << "reply: " << login_text;
	}
}