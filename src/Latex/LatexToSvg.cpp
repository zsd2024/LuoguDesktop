#include "LatexToSvg.h"

Latex::Latex()
{
	webView = new QWebEngineView();
	webView->setHtml(
		R"(
)");
	QEventLoop loop;
	connect(webView, QWebEngineView::loadFinished, [&loop]()
			{ loop.quit(); });
	loop.exec();
}

Latex::~Latex()
{
	delete webView;
}

QString Latex::LatexToURICode(const QString &latexCode, const bool &is_big)
{
	QString jsCode = QString("latexToDataURI(String.raw`%1`, %2).then(uri=>uri);").arg(latexCode).arg(is_big ? "true" : "false");
	QEventLoop loop;
	QString result;

	qDebug() << jsCode;

	webView->page()->runJavaScript(jsCode, [&result, &loop](const QVariant &v)
								   {
				if (v.isNull()) {
					qDebug() << "JavaScript 返回空结果！";
				} else {
					// result = ;
					qDebug() << v.type(); //"生成的 Data URI:" << result;
				}
				loop.quit(); });
}

loop.exec();

return result;
}