#ifndef ERROR_H
#define ERROR_H
#define NewInternalError(ErrorMessage) Error().InternalError(ErrorMessage, __FILE_NAME__, __LINE__, __func__)
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
class Error : public QObject
{
	Q_OBJECT
public:
	Error();
	~Error();
	int InternalError(const QString &ErrorMessage, const QString &ErrorFile, const int &ErrorLine, const QString &ErrorFuntion);
};
#endif