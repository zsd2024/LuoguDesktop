#include "LatexToSvg.h"

LatexToSvg::LatexToSvg(QObject *parent)
	: QObject(parent), webView(new QWebEngineView), channel(new QWebChannel(this))
{
	// 把自己注册到 QWebChannel，JS 端引用名 backend
	channel->registerObject(QStringLiteral("backend"), this);
	webView->page()->setWebChannel(channel);
	webView->setUrl(QUrl("qrc:///html/assets/LatexToSvg.html"));
	QEventLoop load_loop;
	connect(webView, &QWebEngineView::loadFinished, [&load_loop]()
			{ QTimer::singleShot(1000, [&load_loop]()
								 { load_loop.quit(); }); });
	load_loop.exec();
}

LatexToSvg::~LatexToSvg()
{
	delete webView;
}

QString LatexToSvg::LatexToURICode(const QString &latexCode, const bool &is_big)
{
	result.clear();

	// 调用 JS generate(latex,display)
	QString js = QStringLiteral("generate(String.raw`%1`, %2);")
					 .arg(latexCode)
					 .arg(is_big ? "true" : "false");
	webView->page()->runJavaScript(js);

	// 阻塞等待 JS 通过 onDataUriReady/onDataUriError 之一回调
	loop.exec();
	return result;
}

void LatexToSvg::onDataUriReady(const QString &uri)
{
	result = uri;
	loop.quit();
}

void LatexToSvg::onDataUriError(const QString &error)
{
	result = QStringLiteral("ERROR: %1").arg(error);
	loop.quit();
}