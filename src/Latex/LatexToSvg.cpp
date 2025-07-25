#include "LatexToSvg.h"

LatexToSvg::LatexToSvg(QString color, QObject *parent)
	: QObject(parent), webView(new QWebEngineView), channel(new QWebChannel(this)), color(color)
{
	// 把自己注册到 QWebChannel，JS 端引用名 backend
	channel->registerObject(QStringLiteral("backend"), this);
	webView->page()->setWebChannel(channel);
	webView->setUrl(QUrl("qrc:///html/assets/LatexToSvg.html"));
	// 创建进度对话框（范围 0–100），并移除取消按钮
	QProgressDialog *progressDlg = new QProgressDialog("正在初始化 Latex 渲染模块...", QString(), 0, 100, nullptr);
	progressDlg->setWindowModality(Qt::WindowModal);
	progressDlg->setAutoClose(false);
	progressDlg->setAutoReset(false);

	// 隐藏取消按钮
	progressDlg->setCancelButton(nullptr);

	// 将 loadProgress 信号连接到进度对话框
	connect(webView, &QWebEngineView::loadProgress,
			[progressDlg, this](int value)
			{ progressDlg->setValue(value); });

	// 显示对话框并开始加载
	progressDlg->show();

	QEventLoop load_loop;
	connect(webView, &QWebEngineView::loadFinished, [&load_loop, progressDlg]()
			{ progressDlg->hide(); delete progressDlg; load_loop.quit(); });
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
	QString js = QStringLiteral("generate(String.raw`%1`, %2, \"%3\");")
					 .arg(latexCode)
					 .arg(is_big ? "true" : "false")
					 .arg(color);
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