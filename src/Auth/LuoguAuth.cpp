#include "LuoguAuth.h"

LuoguAuth::LuoguAuth()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
	client = new Poco::Net::HTTPSClientSession("www.luogu.com.cn", 443);
}

LuoguAuth::~LuoguAuth()
{
	Poco::Net::uninitializeNetwork();
	Poco::Net::uninitializeSSL();
	delete client;
}

/// @brief 登录
/// @param username 用户名
/// @param password 密码
/// @param captcha 验证码
/// @return 登录信息
QJsonObject LuoguAuth::operator()(QString username, QString password, QString captcha)
{
	return login(username, password, captcha);
}

/// @brief 获取模拟的浏览器 UA
/// @return 浏览器 UA
inline QByteArray LuoguAuth::getUserAgent()
{
	return User_Agent.toUtf8();
}

/// @brief 获取用户名
/// @return 用户名
QString LuoguAuth::get_username()
{
	return username;
}

int LuoguAuth::get_uid()
{
	return std::atoi(cookie.get("_uid").c_str());
}

/// @brief 获取验证码图片
/// @return 验证码
QPixmap LuoguAuth::get_captcha()
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
		request.set("content-type", "image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5");
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
	return captcha;
}

/// @brief 获取 csrf-token
/// @return csrf-token
QJsonObject LuoguAuth::getCsrfToken()
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
	return {{"csrf-token", csrf_token}};
}

/// @brief 登录
/// @param username 用户名
/// @param password 密码
/// @param captcha 验证码
/// @return 登录信息
QJsonObject LuoguAuth::login(QString username, QString password, QString captcha)
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
			this->username = (QJsonDocument::fromJson(login_text.toUtf8()).object())["username"].toString();
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
	QJsonObject json = QJsonDocument::fromJson(login_text.toUtf8()).object();
	QJsonObject cookies;
	for (std::pair<std::string, std::string> i : cookie)
		cookies.insert(i.first.c_str(), i.second.c_str());
	json.insert("cookie", cookies);
	return json;
}

/// @brief 获取用户详细信息
/// @param uid 用户的 uid
/// @param cache 是否使用缓存，默认为 true
/// @return 用户详细信息
QJsonObject LuoguAuth::user_info(int uid, bool cache)
{
	if (!user_info_cache.empty() && cache)
		return user_info_cache;
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			("/user/" + std::to_string(uid)).c_str(),
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
			if (text.contains("<script>window._feInjection = JSON.parse(decodeURIComponent(\""))
			{
				QString user_info_url = text.split("<script>window._feInjection = JSON.parse(decodeURIComponent(\"")[1].split("\"));")[0];
				QString user_info_text = QUrl::fromPercentEncoding(user_info_url.toUtf8());
				QJsonDocument user_info_json = QJsonDocument::fromJson(user_info_text.toUtf8());
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					cookie.set(i.getName(), i.getValue());
				return user_info_cache = user_info_json.object();
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
	return {};
}

/// @brief 登出
/// @return 是否成功
bool LuoguAuth::logout()
{
	QJsonObject csrf_token = getCsrfToken();
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_POST,
			"/auth/logout",
			Poco::Net::HTTPMessage::HTTP_1_1);
		request.setCookies(cookie);
		// request.set("Host", "www.luogu.com.cn");
		request.set("User-Agent", getUserAgent().toStdString());
		request.set("Referer", "https://www.luogu.com.cn/");
		request.set("X-Csrf-Token", csrf_token["csrf-token"].toString().toStdString());

		request.setContentLength(0);
		client->sendRequest(request);

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
				return true;
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
			login_text = QJsonDocument({{"error", QJsonDocument::fromJson(QByteArray::fromStdString(responseBody))["errorMessage"]}}).toJson();
			return false;
		}
	}
	catch (const Poco::Exception &e)
	{
		qDebug() << "Poco异常: " << e.displayText().c_str();
		return false;
	}
	catch (const std::exception &e)
	{
		qDebug() << "标准异常: " << e.what();
		return false;
	}
	catch (...)
	{
		qDebug() << "未知异常";
		return false;
	}
	return false;
}