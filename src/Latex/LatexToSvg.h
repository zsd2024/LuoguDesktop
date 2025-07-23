#ifndef LATEX_TO_SVG_H
#define LATEX_TO_SVG_H

#include <QObject>
#include <QWebEngineView>
#include <QWebChannel>
#include <QEventLoop>
#include <QTimer>

class LatexToSvg : public QObject
{
	Q_OBJECT
public:
	explicit LatexToSvg(QObject *parent = nullptr);
	~LatexToSvg();
	QString LatexToURICode(const QString &latexCode, const bool &is_big);

public slots:
	// JS 调用回调
	void onDataUriReady(const QString &uri);
	void onDataUriError(const QString &error);

private:
	QWebEngineView *webView;
	QWebChannel *channel;
	QString result;
	QEventLoop loop;
};

#endif // LATEX_TO_SVG_H