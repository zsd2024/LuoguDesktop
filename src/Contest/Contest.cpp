#include "Contest.h"

Contest::Contest()
{
}

Contest::~Contest()
{
}

QJsonArray Contest::getContests()
{
	try
	{
		Poco::Net::HTTPRequest request(
			Poco::Net::HTTPRequest::HTTP_GET,
			"/contest/list", Poco::Net::HTTPMessage::HTTP_1_1);
	resend:
		request.setCookies(Common::cookie);
		request.set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
		request.set("referer", "https://www.luogu.com.cn/");
		request.set("x-luogu-type", "content-only");
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
			std::vector<Poco::Net::HTTPCookie> cookies;
			response.getCookies(cookies);
			for (Poco::Net::HTTPCookie i : cookies)
				Common::cookie.set(i.getName(), i.getValue());
			QString text = QString::fromStdString(responseBody), json_text;
			qDebug() << text;
			if (text.contains("<script>window._feInjection = JSON.parse(decodeURIComponent(\""))
			{
				QString url_text = text.split("<script>window._feInjection = JSON.parse(decodeURIComponent(\"")[1].split("\"));")[0];
				json_text = QUrl::fromPercentEncoding(url_text.toUtf8());
				return QJsonDocument::fromJson(json_text.toUtf8()).object()["currentData"].toObject()["contests"].toObject()["result"].toArray();
			}
			else
			{
				QJsonDocument json = QJsonDocument::fromJson(text.toUtf8());
				if (json.isEmpty())
					return {{"error", "匹配失败"}};
				return json.object()["currentData"].toObject()["contests"].toObject()["result"].toArray();
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
	return {{"error", "未知错误"}};
}
