#include "MarkdownViewer.h"

MarkdownViewer::MarkdownViewer() : QWebEngineView()
{
    QFile base_html_file(":/html/assets/MarkdownWithLatexBaseHTML.html", this);
    base_html_file.open(QIODevice::ReadOnly);
    base_html = base_html_file.readAll();
    base_html_file.close();
}

MarkdownViewer::MarkdownViewer(const QString &markdown_with_latex) : QWebEngineView()
{
    setMarkdownWithLatex(markdown_with_latex);
}

MarkdownViewer::~MarkdownViewer() {}

void MarkdownViewer::setMarkdownWithLatex(const QString &markdown_with_latex)
{
    QString modified_markdown = markdown_with_latex;
    modified_markdown.replace("\\", R"(\\)");
    modified_markdown.replace("\"", R"(\")");
    modified_markdown.replace("\'", R"(\')");
    modified_markdown.replace("\n", R"(\n)");
    modified_markdown.replace("\r", R"(\r)");
    modified_markdown.replace("\t", R"(\t)");
    setHtml(base_html.arg(modified_markdown));
}