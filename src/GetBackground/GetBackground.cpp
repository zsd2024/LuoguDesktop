#include "GetBackground.h"

GetBackground::GetBackground()
{
	Poco::Net::initializeNetwork();
	Poco::Net::initializeSSL();
	client = new Poco::Net::HTTPSClientSession("www.bing.com", 443);
}

GetBackground::~GetBackground()
{
	Poco::Net::uninitializeNetwork();
	Poco::Net::uninitializeSSL();
	delete client;
}

QPixmap GetBackground::operator()()
{
	return get_background();
}

inline QByteArray GetBackground::getUserAgent()
{
	return User_Agent.toUtf8();
}

QPixmap GetBackground::get_background()
{
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			get_background_url().toStdString(),
			// "/th?id=OHR.WatertowerMannheim_ZH-CN0692039329_UHD.jpg",
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.set("referer", "https://www.bing.com/");
		request.set("content-type", "image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5");
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
			background.loadFromData(QByteArray::fromStdString(responseBody));
			qDebug() << "获取成功：" << background.size().width() << "x" << background.size().height();
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
	return background;
}

QString GetBackground::get_background_url()
{
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			std::string("https://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&pid=hp&uhd=1"),
			Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
		request.set("Accept-Encoding", "identity");
		request.set("Accept-Language", "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
		request.set("Cache-Control", "no-cache");
		request.set("Connection", "keep-alive");
		request.set("DNT", "1");
		request.set("Host", "www.bing.com");
		request.set("Pragma", "no-cache");
		request.set("Priority", "u=0, i");
		request.set("referer", "https://www.bing.com/");
		request.set("Sec-Fetch-Dest", "document");
		request.set("Sec-Fetch-Mode", "navigate");
		request.set("Sec-Fetch-Site", "none");
		request.set("Sec-Fetch-User", "?1");
		request.set("Sec-GPC", "1");
		request.set("TE", "trailers");
		request.set("Upgrade-Insecure-Requests", "1");
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
			QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(responseBody));
			QString basic_url = jsonDoc.object().value("images").toArray().at(0).toObject().value("url").toString();
			qDebug() << "获取到的json: " << jsonDoc;
			// 正则表达式匹配图片链接
			QRegularExpression pattern("^\\/th\\?id=([^&]+)&rf=([^&]+)&pid=hp");
			QRegularExpressionMatch match = pattern.match(basic_url);
			if (match.hasMatch())
			{
				QString image_url = match.captured(0);
				qDebug() << "获取到的背景图片链接: " << image_url;
				return image_url;
			}
			qDebug() << "获取背景图片链接失败，未匹配到正则表达式";
			return "error";
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
	return "error";
}