#ifndef CONFIG_H
#define CONFIG_H
#include "../Error/Error.h"
#include <KMessageDialog>
#include <QAnyStringView>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStyle>
class Config : public QObject
{
	Q_OBJECT
public:
	Config();
	~Config();
	bool getAutoPunch();
	void setAutoPunch(bool value);

private:
	QSettings *settings;
	const QString configFileName = "config.ini";
};
#endif