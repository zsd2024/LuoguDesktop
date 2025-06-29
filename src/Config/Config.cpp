#include "Config.h"

Config::Config()
{
	QDir configDir = QDir(QCoreApplication::applicationDirPath());
	settings = new QSettings(configDir.filePath("config.ini"), QSettings::IniFormat);
}

Config::~Config()
{
	delete settings;
}

bool Config::getAutoPunch()
{
	if (!settings->contains(QAnyStringView(QString("tools/auto_punch"))))
	{
		QMessageBox msgBox(QMessageBox::Question, "配置设置", "是否开启自动打卡？", QMessageBox::Yes | QMessageBox::No, nullptr);
		msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
		QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());
		if (reply == QMessageBox::Yes)
			setAutoPunch(true);
		else
			setAutoPunch(false);
	}
	return settings->value(QAnyStringView(QString("tools/auto_punch"))).toBool();
}

void Config::setAutoPunch(bool value)
{
	settings->setValue(QAnyStringView(QString("tools/auto_punch")), value);
}