#ifndef MARKDOWN_VIEWER_H
#define MARKDOWN_VIEWER_H
#include <QWebEngineView>
class MarkdownViewer : public QWebEngineView
{
public:
	explicit MarkdownViewer();
	explicit MarkdownViewer(const QString &markdown_with_latex);
	~MarkdownViewer();
	void setMarkdownWithLatex(const QString &markdown_with_latex);
};
#endif