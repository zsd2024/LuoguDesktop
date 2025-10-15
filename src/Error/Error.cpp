#include "Error.h"
#include <qlogging.h>

Error::Error()
{
}

Error::~Error()
{
}

int Error::InternalError(const QString &ErrorMessage, const QString &ErrorFile, const int &ErrorLine, const QString &ErrorFuntion)
{
	qDebug() << "Internal Error:" << ErrorMessage << "in" << ErrorFile << "at line" << ErrorLine << "in function" << ErrorFuntion;
	KMessageDialog *msgBox = new KMessageDialog(KMessageDialog::Type::Error, tr("很抱歉，发生了内部错误。"));
	msgBox->setCaption("错误");
	msgBox->setButtons(KStandardGuiItem::ok());
	msgBox->setAttribute(Qt::WA_DeleteOnClose);
	msgBox->setWindowModality(Qt::WindowModal);
	msgBox->setWindowIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxCritical));
	msgBox->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxCritical));
	msgBox->setDetails(tr("错误信息：") + ErrorMessage + '\n' + tr("错误文件：") + ErrorFile + '\n' + tr("错误行号：") + QString::fromStdString(std::to_string(ErrorLine)) + '\n' + tr("错误函数：") + ErrorFuntion);
	return msgBox->exec();
}