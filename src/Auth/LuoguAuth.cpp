#include "LuoguAuth.h"
#include <cstdlib>

LuoguAuth::LuoguAuth()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
}

LuoguAuth::~LuoguAuth()
{
	Poco::Net::uninitializeNetwork();
	Poco::Net::uninitializeSSL();
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

/// @brief 获取用户名
/// @return 用户名
QString LuoguAuth::get_username()
{
	return username;
}

int LuoguAuth::get_uid()
{
	return std::atoi(Common::Common::cookie.get("_uid").c_str());
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
		request.setCookies(Common::cookie);
		request.set("Accept", "image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5");
		request.set("referer", "https://www.luogu.com.cn/");
		request.set("x-luogu-type", "content-only");
		request.set("User-Agent", /*Common::getUserAgent()*/ "");

		// 发送请求
		Common::client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			captcha.loadFromData(QByteArray::fromStdString(responseBody));
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				Common::cookie.set(i.getName(), i.getValue());
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					Common::cookie.set(i.getName(), i.getValue());
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

/// @brief 登录
/// @param username 用户名
/// @param password 密码
/// @param captcha 验证码
/// @return 登录信息
QJsonObject LuoguAuth::login(QString username, QString password, QString captcha)
{
	QJsonObject csrf_token = Common::getCsrfToken();
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_POST,
			"/do-auth/password",
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(Common::cookie);
		// request.set("Host", "www.luogu.com.cn");
		request.set("User-Agent", Common::getUserAgent());
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
		std::ostream &requestStream = Common::client->sendRequest(request);
		requestStream << body;
		requestStream.flush();

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

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
				Common::cookie.set(i.getName(), i.getValue());
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND || response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_TEMPORARY_REDIRECT)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					Common::cookie.set(i.getName(), i.getValue());
				qDebug() << "已找到，重定向至：" << new_url;
				request.setURI(new_url);
				goto resend;
			}
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
			login_text = QJsonDocument(QJsonObject({{"error", QJsonDocument::fromJson(QByteArray::fromStdString(responseBody))["errorMessage"]}})).toJson();
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
	for (std::pair<std::string, std::string> i : Common::cookie)
		cookies.insert(i.first.c_str(), i.second.c_str());
	json.insert("Common::cookie", cookies);
	return json;
}

QJsonObject LuoguAuth::get_elo_info_page(int uid, int page, int limit)
{
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			("/api/rating/elo?user=" + std::to_string(uid) + "&page=" + std::to_string(page) + "&limit=" + std::to_string(limit)).c_str(),
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(Common::cookie);
		request.set("referer", "https://www.luogu.com.cn/user/" + std::to_string(uid));
		request.set("User-Agent", Common::getUserAgent());

		// 发送请求
		Common::client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			captcha.loadFromData(QByteArray::fromStdString(responseBody));
			QString text = QString::fromStdString(responseBody);
			QJsonDocument elo_info_json = QJsonDocument::fromJson(text.toUtf8());
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				Common::cookie.set(i.getName(), i.getValue());
			return elo_info_json.object();
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					Common::cookie.set(i.getName(), i.getValue());
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
		request.setCookies(Common::cookie);
		request.set("referer", "https://www.luogu.com.cn/user/" + std::to_string(uid));
		request.set("User-Agent", Common::getUserAgent());

		// 发送请求
		Common::client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

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
					Common::cookie.set(i.getName(), i.getValue());
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
					Common::cookie.set(i.getName(), i.getValue());
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

QJsonObject LuoguAuth::elo_info(int uid, bool cache)
{
	if (!elo_info_cache.empty() && cache)
		return elo_info_cache;
	QJsonArray results;
	int count;
	for (int i = 1;; ++i)
	{
		QJsonObject elo_info_page = get_elo_info_page(uid, i, 10);
		if (elo_info_page["records"].toObject()["result"].toArray().size() == 0)
		{
			count = elo_info_page["records"].toObject()["count"].toInt();
			break;
		}
		for (const QJsonValue &value : elo_info_page["records"].toObject()["result"].toArray())
			results.append(value);
	}
	return elo_info_cache = {{"count", count},
							 {"result", results}};
}

bool LuoguAuth::punch()
{
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			"/index/ajax_punch",
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(Common::cookie);
		request.set("referer", "https://www.luogu.com.cn/");
		request.set("User-Agent", Common::getUserAgent());

		// 发送请求
		Common::client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
			return true;
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND)
			{
				std::string new_url = response.get("Location");
				std::vector<Poco::Net::HTTPCookie> cookies;
				response.getCookies(cookies);
				for (Poco::Net::HTTPCookie i : cookies)
					Common::cookie.set(i.getName(), i.getValue());
				qDebug() << "已找到，重定向至：" << new_url;
				request.setURI(new_url);
				goto resend;
			}
			else if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED)
				return true;
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
			punch_info_cache = QString::fromStdString(responseBody);
			return false;
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
	return false;
}

QString LuoguAuth::punch_info()
{
	return punch_info_cache;
}

/// @brief 登出
/// @return 是否成功
bool LuoguAuth::logout()
{
	QJsonObject csrf_token = Common::getCsrfToken();
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_POST,
			"/auth/logout",
			Poco::Net::HTTPMessage::HTTP_1_1);
		request.setCookies(Common::cookie);
		// request.set("Host", "www.luogu.com.cn");
		request.set("User-Agent", Common::getUserAgent());
		request.set("Referer", "https://www.luogu.com.cn/");
		request.set("X-Csrf-Token", csrf_token["csrf-token"].toString().toStdString());

		request.setContentLength(0);
		Common::client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = Common::client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			login_text = QString::fromStdString(responseBody);
			qDebug() << responseBody;
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				Common::cookie.set(i.getName(), i.getValue());
		}
		else
		{
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_FOUND || response.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_TEMPORARY_REDIRECT)
				return true;
			qDebug() << "请求失败! 状态码: " << response.getStatus();
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
			qDebug() << "请求失败! 内容: " << responseBody;
			login_text = QJsonDocument(QJsonObject({{"error", QJsonDocument::fromJson(QByteArray::fromStdString(responseBody))["errorMessage"]}})).toJson();
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