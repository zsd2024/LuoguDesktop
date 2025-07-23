#ifndef MARKDOWN_VIEWER_H
#define MARKDOWN_VIEWER_H
#include <QTextBrowser>
#include <QSvgRenderer>
#include <QWheelEvent>
#include "../Latex/LatexToSvg.h"
class MarkdownViewer : public QTextBrowser
{
public:
	explicit MarkdownViewer(QWidget *parent = nullptr);
	~MarkdownViewer();
	void setMarkdownWithLatex(const QString &markdown_with_latex);

private:
	LatexToSvg *latex_to_svg;
	QString markdown_with_latex;
	void updateCache();
	void updateContent();
	QVector<QString> cache;

protected:
	void wheelEvent(QWheelEvent *event) override;
};
#endif