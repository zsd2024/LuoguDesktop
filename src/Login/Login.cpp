#include "Login.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui_LoginWindow)
{
	ui->setupUi(this);
	connect(ui->captcha_image, &QPushButton::clicked, [this]()
			{ on_captcha_image_clicked(); });
	connect(ui->LoginButton, &QPushButton::clicked, [this]()
			{ on_LoginButton_clicked(); });

	connect(ui->username_lineEdit, &QLineEdit::returnPressed, [this]()
			{ ui->password_lineEdit->setFocus(); });
	connect(ui->password_lineEdit, &QLineEdit::returnPressed, [this]()
			{ ui->captcha_lineEdit->setFocus(); });
	connect(ui->captcha_lineEdit, &QLineEdit::returnPressed, [this]()
			{ on_LoginButton_clicked(); });
	auth = std::make_shared<LuoguAuth>();
	succeed = false;
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::start()
{
	this->show();
	on_captcha_image_clicked();
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
	if (succeed)
	{
		event->accept();
		return;
	}
	KMessageDialog *msgBox = new KMessageDialog(KMessageDialog::Type::WarningTwoActions, tr("登录未完成，确定关闭？"), this);
	msgBox->setCaption(tr("关闭确认"));
	msgBox->setButtons(KStandardGuiItem::ok(), KStandardGuiItem::cancel());
	msgBox->setAttribute(Qt::WA_DeleteOnClose);
	msgBox->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	msgBox->setWindowIcon(QIcon(":/images/assets/logo.svg"));
	msgBox->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxWarning));
	int reply = msgBox->exec();
	if (reply == KMessageDialog::ButtonType::PrimaryAction)
		event->accept();
	else
		event->ignore();
}

void LoginWindow::on_LoginButton_clicked()
{
	try
	{
		QJsonObject res = (*auth)(ui->username_lineEdit->text(), ui->password_lineEdit->text(), ui->captcha_lineEdit->text());
		if (res.contains("error"))
		{
			// 弹出错误弹窗
			KMessageDialog *msgBox = new KMessageDialog(KMessageDialog::Type::Error, res["error"].toString(), this);
			msgBox->setCaption(tr("登录失败"));
			msgBox->setButtons(KStandardGuiItem::ok());
			msgBox->setAttribute(Qt::WA_DeleteOnClose);
			msgBox->setWindowIcon(QIcon(":/images/assets/logo.svg"));
			msgBox->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxCritical));
			msgBox->setDetails("你好");
			msgBox->exec();
			on_captcha_image_clicked();
			ui->captcha_lineEdit->setText("");
			succeed = false;
		}
		else
		{
			KMessageDialog *msgBox = new KMessageDialog(KMessageDialog::Type::Information, tr("欢迎回来，%0！").arg(res["username"].toString()), this);
			msgBox->setCaption(tr("登录成功"));
			msgBox->setButtons(KStandardGuiItem::ok());
			msgBox->setAttribute(Qt::WA_DeleteOnClose);
			msgBox->setWindowIcon(QIcon(":/images/assets/logo.svg"));
			msgBox->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation));
			msgBox->exec();
			cookie = res["cookie"].toObject();
			qDebug() << cookie;
			succeed = true;
			close();
			emit LoginSucceed();
		}
	}
	catch (const std::exception &e)
	{
		NewInternalError(e.what());
	}
}

void LoginWindow::on_captcha_image_clicked()
{
	QPixmap pixmap = QPixmap(auth->get_captcha());
	ui->captcha_image->setIcon(pixmap);
	ui->captcha_image->setIconSize(pixmap.size());
}

std::shared_ptr<LuoguAuth> LoginWindow::get_auth()
{
	return auth;
}