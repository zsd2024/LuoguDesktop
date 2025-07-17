#include "LatexToSvg.h"

Latex::Latex()
{
	webView = new QWebEngineView();
	webView->setHtml(
		R"(<!DOCTYPE html>
<html lang="zh">

<head>
	<meta charset="UTF-8">
	<title>LaTeX to Data URI</title>

	<!-- 配置 MathJax -->
	<script>
		window.MathJax = {
			loader: {
				load: ['input/tex', 'output/svg']
			},
			tex: {
				packages: ['base', 'ams']
			},
			svg: {
				fontCache: 'none'
			},
			startup: {
				typeset: false
			}
		};
	</script>
	<script src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js"></script>
</head>

<body>
	<script>
		async function latexToDataURI(latex, is_big) {
			const node = await MathJax.tex2svgPromise(latex, { display: is_big });
			const svg = node.querySelector('svg').outerHTML;

			const encoded = encodeURIComponent(svg)
				.replace(/'/g, '%27')
				.replace(/"/g, '%22');

			const dataUri = 'data:image/svg+xml;charset=utf-8,' + encoded;
			return dataUri;
		}
	</script>
</body>

</html>
)");
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

	connect(webView, &QWebEngineView::loadFinished, [this, &result, jsCode, &loop](bool ok)
			{
		if (ok) {
			webView->page()->runJavaScript(jsCode, [&result, &loop](const QVariant &v)
				{
				if (v.isNull()) {
					qDebug() << "JavaScript 返回空结果！";
				} else {
					result = v.toString();
					qDebug() << "生成的 Data URI:" << result;
				}
				loop.quit(); });
		} });

	loop.exec();

	return result;
}