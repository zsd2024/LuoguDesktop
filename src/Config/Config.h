#ifndef CONFIG_H
#define CONFIG_H
#include <QObject>
#include <QSettings>
#include <QString>
#include <QAnyStringView>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>
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