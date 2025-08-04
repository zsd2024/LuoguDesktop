#include "MarkdownViewer.h"

MarkdownViewer::MarkdownViewer() : QWebEngineView()
{
}

MarkdownViewer::MarkdownViewer(const QString &markdown_with_latex = "") : QWebEngineView()
{
    setMarkdownWithLatex(markdown_with_latex);
}

MarkdownViewer::~MarkdownViewer() {}

void MarkdownViewer::setMarkdownWithLatex(const QString &markdown_with_latex)
{
    setHtml(QString(R"(
<div id="content"></div>
<script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/mathjax@2.7.9/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script>
    var div = document.getElementById('content');
    var div2 = document.createElement('div');
    div2.innerHTML = String.raw`%1`;
    MathJax.Hub.Queue(
        ['Typeset', MathJax.Hub, div2],
        function() {
            div.innerHTML = marked.parse(div2.innerHTML);
        }
    );
</script>
)")
                .arg(markdown_with_latex));
}