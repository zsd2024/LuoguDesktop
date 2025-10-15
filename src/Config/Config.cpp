#include "Config.h"

Config::Config()
{
	QDir configDir = QDir(QCoreApplication::applicationDirPath());
	settings = new QSettings(configDir.filePath("config.ini"), QSettings::IniFormat);
	if (settings->status() != QSettings::NoError)
		NewInternalError("无法读取配置文件");
}

Config::~Config()
{
	delete settings;
}

bool Config::getAutoPunch()
{
	if (!settings->contains(QAnyStringView(QString("tools/auto_punch"))))
	{
		KMessageDialog *msgBox = new KMessageDialog(KMessageDialog::Type::QuestionTwoActions, tr("是否开启自动打卡？"));
		msgBox->setCaption("配置设置");
		KGuiItem yes(tr("是（&Y）"), QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_DialogYesButton));
		KGuiItem no(tr("否（&N）"), QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_DialogNoButton));
		msgBox->setButtons(yes, no);
		msgBox->setAttribute(Qt::WA_DeleteOnClose);
		msgBox->setWindowModality(Qt::WindowModal);
		msgBox->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
		msgBox->setWindowIcon(QIcon(":/images/assets/logo.svg"));
		msgBox->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxQuestion));
		int reply = msgBox->exec();
		if (reply == KMessageDialog::ButtonType::PrimaryAction)
			setAutoPunch(true);
		else
			setAutoPunch(false);
	}
	return settings->value(QStringLiteral("tools/auto_punch")).toBool();
}

void Config::setAutoPunch(bool value)
{
	settings->setValue(QStringLiteral("tools/auto_punch"), value);
}