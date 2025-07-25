#include "MarkdownViewer.h"

MarkdownViewer::MarkdownViewer(QWidget *parent) : QTextBrowser(parent)
{
	latex_to_svg = new LatexToSvg("#000000", this);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
		latex_to_svg = new LatexToSvg("#ffffff", this);
#endif
}

MarkdownViewer::~MarkdownViewer()
{
	delete latex_to_svg;
}

void MarkdownViewer::setMarkdownWithLatex(const QString &markdown_with_latex)
{
	this->markdown_with_latex = markdown_with_latex;
	updateCache();
	updateContent();
}

void MarkdownViewer::updateCache()
{
	QString input = markdown_with_latex;
	int len = input.size();
	int i = 0;

	while (i < len)
	{
		if (input[i] == '$')
		{
			int delimLen = 1;
			if (i + 1 < len && input[i + 1] == '$')
			{
				delimLen = 2;
			}

			// 检查是否为转义的 $
			if (i > 0 && input[i - 1] == '\\')
			{
				// output += input[i]; // 保留转义的 $
				++i;
				continue;
			}

			int start = i + delimLen;
			bool closed = false;
			QString content;

			while (start < len)
			{
				// 检查是否匹配闭合的同类型美元符
				if (input[start] == '$')
				{
					bool matched = true;
					for (int d = 0; d < delimLen; ++d)
					{
						if (start + d >= len || input[start + d] != '$')
						{
							matched = false;
							break;
						}
					}
					if (matched)
					{
						content = input.mid(i + delimLen, start - i - delimLen);
						i = start + delimLen; // 跳过闭合美元
						closed = true;
						break;
					}
				}

				// 处理转义字符
				if (input[start] == '\\' && start + 1 < len && input[start + 1] == '$')
				{
					++start; // 跳过反斜杠
				}

				++start;
			}

			if (closed)
			{
				// 行间公式：delimLen == 2，行内公式：delimLen == 1
				bool isDisplay = (delimLen == 2);
				QString svg = latex_to_svg->LatexToURICode(content, isDisplay);
				cache.push_back(svg);
			}
			else
			{
				// 如果没有闭合，原样保留
				// output += input.mid(i, delimLen);
				i += delimLen;
			}
		}
		else
		{
			// output += input[i]; // 普通字符直接添加
		}
		++i;
	}
	// setMarkdown(output);
}

void MarkdownViewer::updateContent()
{
	int cache_pos = -1;

	QFont font = this->font();
	int fontSize = font.pointSize(); // 或 font.pixelSize()

	QString input = markdown_with_latex, output;
	output.clear();
	int len = input.size();
	int i = 0;

	while (i < len)
	{
		if (input[i] == '$')
		{
			int delimLen = 1;
			if (i + 1 < len && input[i + 1] == '$')
			{
				delimLen = 2;
			}

			// 检查是否为转义的 $
			if (i > 0 && input[i - 1] == '\\')
			{
				output += input[i]; // 保留转义的 $
				++i;
				continue;
			}

			int start = i + delimLen;
			bool closed = false;
			QString content;

			while (start < len)
			{
				// 检查是否匹配闭合的同类型美元符
				if (input[start] == '$')
				{
					bool matched = true;
					for (int d = 0; d < delimLen; ++d)
					{
						if (start + d >= len || input[start + d] != '$')
						{
							matched = false;
							break;
						}
					}
					if (matched)
					{
						content = input.mid(i + delimLen, start - i - delimLen);
						i = start + delimLen; // 跳过闭合美元
						closed = true;
						break;
					}
				}

				// 处理转义字符
				if (input[start] == '\\' && start + 1 < len && input[start + 1] == '$')
				{
					++start; // 跳过反斜杠
				}

				++start;
			}

			if (closed)
			{
				// 行间公式：delimLen == 2，行内公式：delimLen == 1
				bool isDisplay = (delimLen == 2);
				QString svg = cache[++cache_pos];
				QByteArray svgData = QByteArray::fromPercentEncoding(svg.mid(33).toUtf8());
				QRegularExpression heightRegex(R"raw(height="((\d+\.?\d*)ex)")raw");
				QRegularExpressionMatch heightMatch = heightRegex.match(svgData);
				if (isDisplay)
					output += "<br/><p align='center'>";
				output += "<img src=\"";
				output += svg; // 用SVG替换公式
				output += "\" alt=\"Latex 公式\" ";
				if (heightMatch.hasMatch())
				{
					output += "height=\"";
					output += QString::fromStdString(std::to_string(heightMatch.captured(2).toDouble() * (isDisplay ? 1.5 : 1.0) * fontSize));
					output += "\" ";
				}
				output += "/>";
				if (isDisplay)
					output += "</p><br/>";
			}
			else
			{
				// 如果没有闭合，原样保留
				output += input.mid(i, delimLen);
				i += delimLen;
			}
		}
		else
		{
			output += input[i]; // 普通字符直接添加
		}
		++i;
	}
	setMarkdown(output);
}

void MarkdownViewer::wheelEvent(QWheelEvent *event)
{
	QTextBrowser::wheelEvent(event);
	if (event->modifiers() & Qt::ControlModifier)
		updateContent();
}
