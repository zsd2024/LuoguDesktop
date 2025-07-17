#ifndef LATEX_TO_SVG_H
#define LATEX_TO_SVG_H

#include <QObject>
#include <QWebEngineView>
#include <QEventLoop>

class Latex : public QObject
{
	Q_OBJECT
public:
	Latex();
	~Latex();
	QString LatexToURICode(const QString &latexCode, const bool &is_big);

private:
	QWebEngineView *webView;
};

#endif // LATEX_TO_SVG_H