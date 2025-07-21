#include "Common.h"

Poco::Net::Context *Common::pCtx;
QString Common::csrf_token;
QString Common::C3VK;
Poco::Net::HTTPSClientSession *Common::client;
Poco::Net::NameValueCollection Common::cookie;

Common::Common()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
	pCtx = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", QDir(QCoreApplication::applicationDirPath()).filePath("cacert.pem").toStdString(), Poco::Net::Context::VERIFY_RELAXED, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	client = new Poco::Net::HTTPSClientSession("www.luogu.com.cn", 443, pCtx);
}

Common::~Common()
{
	Poco::Net::uninitializeNetwork();
	Poco::Net::uninitializeSSL();
	delete client;
	delete pCtx;
}

void Common::init()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
	pCtx = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", QDir(QCoreApplication::applicationDirPath()).filePath("cacert.pem").toStdString(), Poco::Net::Context::VERIFY_RELAXED, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	client = new Poco::Net::HTTPSClientSession("www.luogu.com.cn", 443, pCtx);
}

std::string Common::getUserAgent()
{
#ifdef _WIN32
#ifdef _WIN64
	return "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36";
#else
	return "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.94 Safari/537.36";
#endif
#else
#ifdef __linux__
	return "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/139.0.0.0 Safari/537.36 Edg/139.0.0.0";
#else
	return "Mozilla/5.0 (Linux; Android 4.0.4; Galaxy Nexus Build/IMM76B) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.133 Mobile Safari/535.19";
#endif
#endif
}

/// @brief 获取 csrf-token
/// @return csrf-token
QJsonObject Common::getCsrfToken()
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
		request.set("User-Agent", getUserAgent());

		// 发送请求
		client->sendRequest(request);

		// 接收响应
		Poco::Net::HTTPResponse response;
		std::istream &responseStream = client->receiveResponse(response);

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			std::string responseBody;
			Poco::StreamCopier::copyToString(responseStream, responseBody);
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