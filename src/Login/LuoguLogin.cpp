#include "LuoguLogin.h"

LuoguLogin::LuoguLogin()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
	client = new Poco::Net::HTTPSClientSession("www.luogu.com.cn", 443);
}

LuoguLogin::~LuoguLogin()
{
	Poco::Net::uninitializeNetwork();
	Poco::Net::uninitializeSSL();
	delete client;
}

QJsonObject LuoguLogin::operator()(QString username, QString password, QString captcha)
{
	return login(username, password, captcha);
}

inline QByteArray LuoguLogin::getUserAgent()
{
	return User_Agent.toUtf8();
}

QPixmap LuoguLogin::get_captcha()
{
	try
	{
		qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			std::string("/lg4/captcha?_t=") + std::to_string(timestamp),
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(cookie);
		request.set("referer", "https://www.luogu.com.cn/");
		request.set("x-luogu-type", "content-only");
		// request.set("content-type", "image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5");
		request.set("User-Agent", /*getUserAgent().toStdString()*/ "");

		// 发送请求
		client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			captcha.loadFromData(QByteArray::fromStdString(responseBody));
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				cookie.set(i.getName(), i.getValue());
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					cookie.set(i.getName(), i.getValue());
				qDebug() << "已找到，重定向至：" << new_url;
				request.setURI(new_url);
				goto resend;
			}
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
		}
	}
	catch (const Poco::Exception &e)
	{
		qDebug() << "Poco异常: " << e.displayText().c_str();
	}
	catch (const std::exception &e)
	{
		qDebug() << "标准异常: " << e.what();
	}
	catch (...)
	{
		qDebug() << "未知异常";
	}

	// client.get("https://www.luogu.com.cn/lg4/captcha")
	// 	.header("referer", "https://www.luogu.com.cn/")
	// 	.header("content-type", "image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5")
	// 	.header("User-Agent", getUserAgent())
	// 	.onSuccess([this](QByteArray byte_text)
	// 			   { captcha.loadFromData(byte_text); })
	// 	.block()
	// 	.exec();
	// QNetworkRequest request(QUrl("https://www.luogu.com.cn/lg4/captcha"));
	// request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, (uint)QNetworkRequest::NoLessSafeRedirectPolicy);
	// request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	// request.setRawHeader("referer", "https://www.luogu.com.cn/");
	// request.setRawHeader("x-luogu-type", "content-only");
	// get_captcha_reply = manager.get(request);
	// QObject::connect(get_captcha_reply, &QNetworkReply::finished, [this]()
	// 				 { get_captcha_finished(get_captcha_reply);
	// 				   get_captcha_reply->deleteLater(); });
	return captcha;
}

// void LuoguLogin::get_captcha_finished(QNetworkReply *reply)
// {
// 	qDebug() << "getCaptcha: finished";
// 	QByteArray byte_text = reply->readAll();
// 	if (byte_text != "")
// 	{
// 		captcha.loadFromData(byte_text);
// 		qDebug() << "captcha: " << captcha;
// 	}
// }

QJsonObject LuoguLogin::getCsrfToken()
{
	if (!csrf_token.isEmpty())
		return {{"csrf-token", csrf_token}};
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			"/",
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(cookie);
		request.set("referer", "https://www.luogu.com.cn/");
		request.set("User-Agent", getUserAgent().toStdString());

		// 发送请求
		client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			captcha.loadFromData(QByteArray::fromStdString(responseBody));
			QString text = QString::fromStdString(responseBody);
			if (text.contains("<script>var _$daewqwskl=[\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\"];var _$oopopdwskl=[\"\\x6f\\x6e\\x4d\\x6f\\x75\\x73\\x65\\x4d\\x6f\\x76\\x65\",\"\\x62\\x6f\\x64\\x79\",\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\",\"\\x72\\x65\\x6d\\x6f\\x76\\x65\\x41\\x74\\x74\\x72\\x69\\x62\\x75\\x74\\x65\"];window.open(\"/\", \"_self\");window[_$daewqwskl[0]].cookie=\"C3VK="))
			{
				C3VK = text.split("window[_$daewqwskl[0]].cookie=\"C3VK=")[1].split(";")[0];
				qDebug() << "C3VK: " << C3VK;
				{
					cookie.set("C3VK", C3VK.toStdString());
				}
				getCsrfToken();
			}
			else if (text.contains("<meta name=\"csrf-token\" content=\""))
			{
				csrf_token = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
				qDebug() << "csrf-token: " << csrf_token;
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					cookie.set(i.getName(), i.getValue());
			}
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					cookie.set(i.getName(), i.getValue());
				qDebug() << "已找到，重定向至：" << new_url;
				request.setURI(new_url);
				goto resend;
			}
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
		}
	}
	catch (const Poco::Exception &e)
	{
		qDebug() << "Poco异常: " << e.displayText().c_str();
	}
	catch (const std::exception &e)
	{
		qDebug() << "标准异常: " << e.what();
	}
	catch (...)
	{
		qDebug() << "未知异常";
	}
	// client.get("https://www.luogu.com.cn/")
	// 	.header("referer", "https://www.luogu.com.cn/")
	// 	.header("User-Agent", getUserAgent())
	// 	.onSuccess([this](QByteArray byte_text)
	// 			   {
	// 	QString text(byte_text);
	// 	if (text.contains("<script>var _$daewqwskl=[\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\"];var _$oopopdwskl=[\"\\x6f\\x6e\\x4d\\x6f\\x75\\x73\\x65\\x4d\\x6f\\x76\\x65\",\"\\x62\\x6f\\x64\\x79\",\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\",\"\\x72\\x65\\x6d\\x6f\\x76\\x65\\x41\\x74\\x74\\x72\\x69\\x62\\x75\\x74\\x65\"];window.open(\"/\", \"_self\");window[_$daewqwskl[0]].cookie=\"C3VK="))
	// 	{
	// 		C3VK = text.split("window[_$daewqwskl[0]].cookie=\"C3VK=")[1].split(";")[0];
	// 		qDebug() << "C3VK: " << C3VK;
	// 		{
	// 			// 创建并添加 cookie
	// 			QNetworkCookie cookie("C3VK", C3VK.toUtf8());
	// 			cookie.setDomain("www.luogu.com.cn");
	// 			cookie.setPath("/");
	// 			client.cookieJar()->insertCookie(cookie);
	// 		}
	// 		getCsrfToken();
	// 	}
	// 	else if (text.contains("<meta name=\"csrf-token\" content=\""))
	// 	{
	// 		csrf_token = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
	// 		qDebug() << "csrf-token: " << csrf_token;
	// 	} })
	// 	.block()
	// 	.exec();
	// QNetworkRequest request(QUrl("https://www.luogu.com.cn/"));
	// request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	// request.setRawHeader("referer", "https://www.luogu.com.cn/");
	// request.setRawHeader("x-luogu-type", "content-only");
	// getCsrfToken_reply = manager.get(request);
	// QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, [this]()
	// 				 { getCsrfToken_finished(getCsrfToken_reply);
	// 				   getCsrfToken_reply->deleteLater(); }); // 在 finished 后 deleteLater
	// QEventLoop loop;
	// QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, [&loop]()
	// 				 { loop.quit(); });
	// loop.exec();
	return {{"csrf-token", csrf_token}};
}

// void LuoguLogin::getCsrfToken_finished(QNetworkReply *reply)
// {
// 	qDebug() << "getCsrfToken: finished";
// 	QByteArray byte_text = reply->readAll();
// 	QString text(byte_text);
// 	auto resend = [this](QUrl url)
// 	{
// 		QNetworkRequest request(url);
// 		request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
// 		request.setRawHeader("referer", "https://www.luogu.com.cn/");
// 		request.setRawHeader("x-luogu-type", "content-only");
// 		QNetworkReply *getCsrfToken_reply = manager.get(request);
// 		if (getCsrfToken_reply != nullptr)
// 			getCsrfToken_reply->deleteLater();
// 		QObject::connect(&manager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply)
// 						 { getCsrfToken_finished(reply); });
// 		QEventLoop loop;
// 		QObject::connect(getCsrfToken_reply, &QNetworkReply::finished, [&loop]()
// 						 { loop.quit(); });
// 		loop.exec();
// 	};
// 	/*if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
// 	{
// 		QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
// 		qDebug() << "redirectUrl: " << redirectUrl;
// 		resend(redirectUrl);
// 	}
// 	else */
// 	if (text != "")
// 		if (text.contains("<script>var _$daewqwskl=[\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\"];var _$oopopdwskl=[\"\\x6f\\x6e\\x4d\\x6f\\x75\\x73\\x65\\x4d\\x6f\\x76\\x65\",\"\\x62\\x6f\\x64\\x79\",\"\\x64\\x6f\\x63\\x75\\x6d\\x65\\x6e\\x74\",\"\\x72\\x65\\x6d\\x6f\\x76\\x65\\x41\\x74\\x74\\x72\\x69\\x62\\x75\\x74\\x65\"];window.open(\"/\", \"_self\");window[_$daewqwskl[0]].cookie=\"C3VK="))
// 		{
// 			C3VK = text.split("window[_$daewqwskl[0]].cookie=\"C3VK=")[1].split(";")[0];
// 			qDebug() << "C3VK: " << C3VK;
// 			{
// 				// 创建并添加 cookie
// 				QNetworkCookie cookie("C3VK", C3VK.toUtf8());
// 				cookie.setDomain("www.luogu.com.cn");
// 				cookie.setPath("/");
// 				manager.cookieJar()->insertCookie(cookie);
// 			}
// 			QList<QNetworkCookie> l = (manager.cookieJar()->cookiesForUrl(QUrl("https://www.luogu.com.cn/")));
// 			for (QNetworkCookie i : l)
// 				qDebug() << i.domain() << " " << i.path() << " " << i.name() << " " << i.value();
// 			resend(QUrl("https://www.luogu.com.cn/"));
// 		}
// 		else if (text.contains("<meta name=\"csrf-token\" content=\""))
// 		{
// 			csrf_token = text.split("<meta name=\"csrf-token\" content=\"")[1].split("\">")[0];
// 			qDebug() << "csrf-token: " << csrf_token;
// 			QList<QNetworkCookie> l = (manager.cookieJar()->cookiesForUrl(QUrl("https://www.luogu.com.cn/")));
// 			for (QNetworkCookie i : l)
// 				qDebug() << i.domain() << " " << i.path() << " " << i.name() << " " << i.value();
// 		}
// }

QJsonObject LuoguLogin::login(QString username, QString password, QString captcha)
{
	QJsonObject csrf_token = getCsrfToken();
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_POST,
			"/do-auth/password",
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(cookie);
		// request.set("Host", "www.luogu.com.cn");
		request.set("User-Agent", getUserAgent().toStdString());
		// request.set("Accept", "application/json, text/plain, */*");
		// request.set("Accept-Language", "zh-CN,en,*");
		// request.set("Accept-Encoding", "zstd, gzip, deflate");
		request.set("Referer", "https://www.luogu.com.cn/auth/login");
		request.set("Content-Type", "application/json");
		request.set("X-Csrf-Token", csrf_token["csrf-token"].toString().toStdString());
		// request.set("X-Requested-With", "XMLHttpRequest");
		// request.set("Origin", "https://www.luogu.com.cn");
		// request.set("DNT", "1");
		// request.set("Sec-GPC", "1");
		// request.set("Connection", "keep-alive");
		// request.set("Sec-Fetch-Dest", "empty");
		// request.set("Sec-Fetch-Mode", "no-cors");
		// request.set("Sec-Fetch-Site", "same-origin");
		// request.set("Priority", "u=4");
		// request.set("Pragma", "no-cache");
		// request.set("Cache-Control", "no-cache");

		std::string body = QJsonDocument({{"username", username},
										  {"password", password},
										  {"captcha", captcha}})
							   .toJson(QJsonDocument::Compact)
							   .toStdString();
		request.setContentLength(body.length());
		std::ostream &requestStream = client->sendRequest(request);
		requestStream << body;
		requestStream.flush();

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			login_text = QString::fromStdString(responseBody);
			qDebug() << responseBody;
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				cookie.set(i.getName(), i.getValue());
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					cookie.set(i.getName(), i.getValue());
				qDebug() << "已找到，重定向至：" << new_url;
				request.setURI(new_url);
				goto resend;
			}
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
			login_text = QJsonDocument({{"error", QJsonDocument::fromJson(QByteArray::fromStdString(responseBody))["errorMessage"]}}).toJson();
		}
	}
	catch (const Poco::Exception &e)
	{
		qDebug() << "Poco异常: " << e.displayText().c_str();
	}
	catch (const std::exception &e)
	{
		qDebug() << "标准异常: " << e.what();
	}
	catch (...)
	{
		qDebug() << "未知异常";
	}
	// QList<QNetworkCookie> l = (client.cookieJar()->cookiesForUrl(QUrl("https://www.luogu.com.cn/")));
	// for (QNetworkCookie i : l)
	// 	qDebug() << i.domain() << " " << i.path() << " " << i.name() << " " << i.value();
	// client.post("https://www.luogu.com.cn/do-auth/password")
	// .body(QJsonObject({{"username", username},
	// 				   {"password", password},
	// 				   {"captcha", captcha}}))
	// 	// .header("Accept", "application/json, text/plain, */*")
	// 	// .header("Referer", "https://www.luogu.com.cn/auth/login")
	// 	// .header("User-Agent", getUserAgent())
	// 	// .header("X-CSRF-TOKEN", csrf_token["csrf-token"].toString().toUtf8())
	// 	// .header("X-Requested-With", "XMLHttpRequest")
	// .header("Host", "www.luogu.com.cn")
	// .header("User-Agent", "Mozilla/5.0")
	// .header("Accept", "application/json, text/plain, */*")
	// .header("Accept-Language", "zh-CN,en,*")
	// .header("Accept-Encoding", "zstd, gzip, deflate")
	// .header("Referer", "https://www.luogu.com.cn/auth/login")
	// .header("Content-Type", "application/json")
	// .header("X-Csrf-Token", csrf_token["csrf-token"].toString().toUtf8())
	// .header("X-Requested-With", "XMLHttpRequest")
	// .header("Content-Length", "63")
	// .header("Origin", "https://www.luogu.com.cn")
	// .header("DNT", "1")
	// .header("Sec-GPC", "1")
	// .header("Connection", "keep-alive")
	// .header("Sec-Fetch-Dest", "empty")
	// .header("Sec-Fetch-Mode", "no-cors")
	// .header("Sec-Fetch-Site", "same-origin")
	// .header("Priority", "u=4")
	// .header("Pragma", "no-cache")
	// .header("Cache-Control", "no-cache")
	// 	.onSuccess([this](QByteArray byte_text)
	// 			   {
	// 		QString replyText = QString::fromUtf8(byte_text);
	// 		qDebug() << "reply: " << replyText;
	// 			login_text = replyText; })
	// 	.onFailed([this](QNetworkReply *byte_text)
	// 			  {
	// 		qDebug() << "reply: " << byte_text->rawHeaderPairs();})
	// 	.repeat(3)
	// 	.block()
	// 	.exec();
	// qDebug() << csrf_token;
	// QNetworkRequest request(QUrl("https://www.luogu.com.cn/do-auth/password"));
	// request.setHeader(QNetworkRequest::UserAgentHeader, User_Agent.at(std::uniform_int_distribution<int>(0, User_Agent.size() - 1)(gen)).toUtf8());
	// request.setRawHeader("referer", "https://www.luogu.com.cn/auth/login");
	// request.setRawHeader("host", "www.luogu.com.cn");
	// request.setRawHeader("origin", "https://www.luogu.com.cn");
	// request.setRawHeader("x-csrf-token", csrf_token["csrf-token"].toString().toUtf8());
	// request.setRawHeader("x-requested-with", "XMLHttpRequest");
	// request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	// qDebug() << "csrf-token: " << csrf_token["csrf-token"].toString();
	// qDebug() << QJsonDocument({{"username", username},
	// 						   {"password", password},
	// 						   {"captcha", captcha}})
	// 				.toJson()
	// 				.toStdString()
	// 				.c_str();
	// login_reply = manager.post(request, QJsonDocument({{"username", username},
	// 												   {"password", password},
	// 												   {"captcha", captcha}})
	// 										.toJson());
	// QObject::connect(login_reply, &QNetworkReply::finished, [this]()
	// 				 { login_finished(login_reply);
	// 				   login_reply->deleteLater(); }); // 在 finished 后 deleteLater
	// QEventLoop loop;
	// QObject::connect(login_reply, &QNetworkReply::finished, [&loop]()
	// 				 { loop.quit(); });
	// loop.exec();
	QJsonObject json = QJsonDocument::fromJson(login_text.toUtf8()).object();
	QJsonObject cookies;
	for (std::pair<std::string, std::string> i : cookie)
		cookies.insert(i.first.c_str(), i.second.c_str());
	json.insert("cookie", cookies);
	return json;
}

// void LuoguLogin::login_finished(QNetworkReply *reply)
// {
// 	qDebug() << "login: finished";
// 	QByteArray byte_text = reply->readAll(); // 只读一次
// 	QString replyText = QString::fromUtf8(byte_text);
// 	qDebug() << "reply: " << replyText;

// 	if (reply->error() != QNetworkReply::NoError)
// 	{
// 		qDebug() << "error: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
// 		login_text = replyText;
// 	}
// 	else
// 	{
// 		login_text = replyText;
// 	}
// 	reply->deleteLater();
// }