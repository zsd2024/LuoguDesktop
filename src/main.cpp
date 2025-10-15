#include "LuoguDesktop.h"

#include <KAboutData>
#include <KTextEdit>
#include <KXmlGuiWindow>
#include <QApplication>
#include <QLocale>
#include <QStringLiteral>
#include <QTranslator>
#pragma comment(lib, "user32.lib")

using namespace Qt::StringLiterals;

LuoguDesktop *w;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	KAboutData aboutData(
		// 内部名称
		u"LuoguDesktop"_s,
		// 显示名称
		LuoguDesktop::tr("LuoguDesktop"),
		// 版本号
		u"0.1 "_s,
		// 简介
		LuoguDesktop::tr(""),
		// 许可证
		KAboutLicense::GPL,
		// 版权声明
		LuoguDesktop::tr("(c) 2025"),
		// 其他信息
		LuoguDesktop::tr("Educational application..."),
		// 官网
		u"https://zsd2024.github.io/LuoguDesktop"_s,
		// 错误报告的邮件地址
		u"zsd2024@outlook.com"_s);
	aboutData.addAuthor(
		// 作者全名
		LuoguDesktop::tr("zsd2024"),
		// 作者角色
		LuoguDesktop::tr(""),
		// 作者邮箱
		u"zsd2024@outlook.com"_s,
		// 作者网站
		u"https://github.com/zsd2024"_s,
		// store.kde.org 中的用户名（用于头像图片）
		u""_s);
	KAboutData::setApplicationData(aboutData);

	QTranslator translator;
	if (translator.load(QLocale::system(), ""_L1, ""_L1, ":/translations/assets/translations"_L1))
		app.installTranslator(&translator);
	qDebug() << translator.filePath();
	w = new LuoguDesktop;
	return app.exec();
}
