/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *Login;
    QVBoxLayout *head;
    QLabel *logo;
    QLabel *motto;
    QVBoxLayout *InformationInput;
    QVBoxLayout *UsernameInput;
    QLabel *username_label;
    QLineEdit *username_lineEdit;
    QVBoxLayout *Password;
    QLabel *password_label;
    QLineEdit *password_lineEdit;
    QVBoxLayout *Captcha;
    QLabel *captcha_label;
    QHBoxLayout *Captcha_Input_Image;
    QLineEdit *captcha_lineEdit;
    QPushButton *captcha_image;
    QPushButton *LoginButton;
    QLabel *Forget_password;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame;
    QHBoxLayout *Three_party_login;
    QSpacerItem *Three_party_login_horizontalSpacer_left;
    QLabel *three_party_login;
    QLabel *wechat;
    QLabel *github;
    QSpacerItem *Three_party_login_horizontalSpacer_right;
    QSpacerItem *verticalSpacer_1;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *NoAuth;
    QSpacerItem *NoAuth_horizontalSpacer_left;
    QLabel *no_auth;
    QLabel *label;
    QSpacerItem *NoAuth_horizontalSpacer_right;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(370, 520);
        LoginWindow->setMinimumSize(QSize(370, 520));
        LoginWindow->setMaximumSize(QSize(370, 520));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/assets/logo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        LoginWindow->setWindowIcon(icon);
        LoginWindow->setStyleSheet(QString::fromUtf8("* {\n"
"    background-color: palette(base);\n"
"}\n"
"\n"
"/* \346\267\261\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"dark\"] {\n"
"    background-color: #2f343f; /* \346\267\261\350\211\262\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"light\"] {\n"
"    background-color: #f7f7f7; /* \346\265\205\350\211\262\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(LoginWindow);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Login = new QVBoxLayout();
        Login->setObjectName(QString::fromUtf8("Login"));
        head = new QVBoxLayout();
        head->setObjectName(QString::fromUtf8("head"));
        logo = new QLabel(LoginWindow);
        logo->setObjectName(QString::fromUtf8("logo"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logo->sizePolicy().hasHeightForWidth());
        logo->setSizePolicy(sizePolicy);
        logo->setMinimumSize(QSize(160, 81));
        logo->setStyleSheet(QString::fromUtf8("border-image: url(:/images/assets/logo.png);"));

        head->addWidget(logo, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        motto = new QLabel(LoginWindow);
        motto->setObjectName(QString::fromUtf8("motto"));
        QPalette palette;
        QBrush brush(QColor(52, 152, 219, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(27, 30, 32, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(98, 108, 118, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        motto->setPalette(palette);
        QFont font;
        font.setUnderline(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        motto->setFont(font);
        motto->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        motto->setWordWrap(false);
        motto->setOpenExternalLinks(false);

        head->addWidget(motto, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        Login->addLayout(head);

        InformationInput = new QVBoxLayout();
        InformationInput->setObjectName(QString::fromUtf8("InformationInput"));
        UsernameInput = new QVBoxLayout();
        UsernameInput->setObjectName(QString::fromUtf8("UsernameInput"));
        username_label = new QLabel(LoginWindow);
        username_label->setObjectName(QString::fromUtf8("username_label"));
        QPalette palette1;
        QBrush brush3(QColor(252, 252, 252, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush4(QColor(252, 252, 252, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush5(QColor(252, 252, 252, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush6(QColor(252, 252, 252, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        username_label->setPalette(palette1);
        QFont font1;
        username_label->setFont(font1);
        username_label->setStyleSheet(QString::fromUtf8("* {\n"
"    color: palette(text);\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \346\267\261\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"dark\"] {\n"
"    color: #ffffff; /* \347\231\275\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"light\"] {\n"
"    color: #000000; /* \351\273\221\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        UsernameInput->addWidget(username_label);

        username_lineEdit = new QLineEdit(LoginWindow);
        username_lineEdit->setObjectName(QString::fromUtf8("username_lineEdit"));
        username_lineEdit->setFont(font1);
        username_lineEdit->setStyleSheet(QString::fromUtf8("font-size: 16px;"));

        UsernameInput->addWidget(username_lineEdit);


        InformationInput->addLayout(UsernameInput);

        Password = new QVBoxLayout();
        Password->setObjectName(QString::fromUtf8("Password"));
        password_label = new QLabel(LoginWindow);
        password_label->setObjectName(QString::fromUtf8("password_label"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush7(QColor(252, 252, 252, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush8(QColor(252, 252, 252, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush9(QColor(252, 252, 252, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        password_label->setPalette(palette2);
        password_label->setFont(font1);
        password_label->setStyleSheet(QString::fromUtf8("* {\n"
"    color: palette(text);\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \346\267\261\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"dark\"] {\n"
"    color: #ffffff; /* \347\231\275\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"light\"] {\n"
"    color: #000000; /* \351\273\221\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        Password->addWidget(password_label);

        password_lineEdit = new QLineEdit(LoginWindow);
        password_lineEdit->setObjectName(QString::fromUtf8("password_lineEdit"));
        password_lineEdit->setFont(font1);
        password_lineEdit->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        password_lineEdit->setEchoMode(QLineEdit::Password);

        Password->addWidget(password_lineEdit);


        InformationInput->addLayout(Password);

        Captcha = new QVBoxLayout();
        Captcha->setObjectName(QString::fromUtf8("Captcha"));
        captcha_label = new QLabel(LoginWindow);
        captcha_label->setObjectName(QString::fromUtf8("captcha_label"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush10(QColor(252, 252, 252, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush11(QColor(252, 252, 252, 128));
        brush11.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush12(QColor(252, 252, 252, 128));
        brush12.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush12);
#endif
        captcha_label->setPalette(palette3);
        captcha_label->setFont(font1);
        captcha_label->setStyleSheet(QString::fromUtf8("* {\n"
"    color: palette(text);\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \346\267\261\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"dark\"] {\n"
"    color: #ffffff; /* \347\231\275\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"light\"] {\n"
"    color: #000000; /* \351\273\221\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        Captcha->addWidget(captcha_label);

        Captcha_Input_Image = new QHBoxLayout();
        Captcha_Input_Image->setObjectName(QString::fromUtf8("Captcha_Input_Image"));
        captcha_lineEdit = new QLineEdit(LoginWindow);
        captcha_lineEdit->setObjectName(QString::fromUtf8("captcha_lineEdit"));
        captcha_lineEdit->setFont(font1);
        captcha_lineEdit->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        captcha_lineEdit->setEchoMode(QLineEdit::Normal);

        Captcha_Input_Image->addWidget(captcha_lineEdit);

        captcha_image = new QPushButton(LoginWindow);
        captcha_image->setObjectName(QString::fromUtf8("captcha_image"));
        captcha_image->setMinimumSize(QSize(90, 35));

        Captcha_Input_Image->addWidget(captcha_image);


        Captcha->addLayout(Captcha_Input_Image);


        InformationInput->addLayout(Captcha);


        Login->addLayout(InformationInput);

        LoginButton = new QPushButton(LoginWindow);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setMinimumSize(QSize(0, 31));
        LoginButton->setFont(font1);
        LoginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: rgb(52, 152, 219); /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    color: #ffffff; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(52, 152, 219,0.9); /* \346\202\254\346\265\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));

        Login->addWidget(LoginButton);

        Forget_password = new QLabel(LoginWindow);
        Forget_password->setObjectName(QString::fromUtf8("Forget_password"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush13(QColor(52, 152, 219, 128));
        brush13.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush13);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush14(QColor(52, 152, 219, 128));
        brush14.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush14);
#endif
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush15(QColor(52, 152, 219, 128));
        brush15.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush15);
#endif
        Forget_password->setPalette(palette4);
        Forget_password->setFont(font1);
        Forget_password->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: none;\n"
"    color: #3498db;; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"   color: #14558f; /* \346\202\254\346\265\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));

        Login->addWidget(Forget_password, 0, Qt::AlignRight|Qt::AlignTop);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->addItem(verticalSpacer_4);

        frame = new QFrame(LoginWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frame->setPalette(palette5);
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);

        Login->addWidget(frame);

        Three_party_login = new QHBoxLayout();
        Three_party_login->setObjectName(QString::fromUtf8("Three_party_login"));
        Three_party_login_horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Three_party_login->addItem(Three_party_login_horizontalSpacer_left);

        three_party_login = new QLabel(LoginWindow);
        three_party_login->setObjectName(QString::fromUtf8("three_party_login"));
        three_party_login->setStyleSheet(QString::fromUtf8("* {\n"
"    color: #888;\n"
"    font-size: 16px;\n"
"}"));

        Three_party_login->addWidget(three_party_login, 0, Qt::AlignRight|Qt::AlignVCenter);

        wechat = new QLabel(LoginWindow);
        wechat->setObjectName(QString::fromUtf8("wechat"));
        wechat->setMinimumSize(QSize(0, 0));
        wechat->setMaximumSize(QSize(20, 18));
        wechat->setStyleSheet(QString::fromUtf8("image: url(:/images/assets/wechat.svg);"));

        Three_party_login->addWidget(wechat, 0, Qt::AlignLeft);

        github = new QLabel(LoginWindow);
        github->setObjectName(QString::fromUtf8("github"));
        github->setMinimumSize(QSize(0, 0));
        github->setMaximumSize(QSize(20, 18));
        github->setStyleSheet(QString::fromUtf8("image: url(:/images/assets/github.svg);"));

        Three_party_login->addWidget(github, 0, Qt::AlignLeft|Qt::AlignVCenter);

        Three_party_login_horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Three_party_login->addItem(Three_party_login_horizontalSpacer_right);


        Login->addLayout(Three_party_login);

        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->addItem(verticalSpacer_1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->addItem(verticalSpacer_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->addItem(verticalSpacer_3);

        NoAuth = new QHBoxLayout();
        NoAuth->setObjectName(QString::fromUtf8("NoAuth"));
        NoAuth_horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        NoAuth->addItem(NoAuth_horizontalSpacer_left);

        no_auth = new QLabel(LoginWindow);
        no_auth->setObjectName(QString::fromUtf8("no_auth"));
        no_auth->setStyleSheet(QString::fromUtf8("* {\n"
"    color: palette(text);\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \346\267\261\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"dark\"] {\n"
"    color: #ffffff; /* \347\231\275\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\346\250\241\345\274\217 */\n"
"[color-scheme=\"light\"] {\n"
"    color: #000000; /* \351\273\221\350\211\262\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        NoAuth->addWidget(no_auth, 0, Qt::AlignRight|Qt::AlignVCenter);

        label = new QLabel(LoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: none;\n"
"    color: #3498db;; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"   color: #14558f; /* \346\202\254\346\265\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));

        NoAuth->addWidget(label, 0, Qt::AlignLeft|Qt::AlignVCenter);

        NoAuth_horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        NoAuth->addItem(NoAuth_horizontalSpacer_right);


        Login->addLayout(NoAuth);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(Login);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225 - LuoguDesktop", nullptr));
        logo->setText(QString());
        motto->setText(QCoreApplication::translate("LoginWindow", "\345\234\250\346\264\233\350\260\267\357\274\214\344\272\253\345\217\227 Coding \347\232\204\346\254\242\344\271\220\357\274\201", nullptr));
        username_label->setText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        username_lineEdit->setText(QString());
        username_lineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215\343\200\201\346\211\213\346\234\272\345\217\267\346\210\226\347\224\265\345\255\220\351\202\256\347\256\261", nullptr));
        password_label->setText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201", nullptr));
        password_lineEdit->setText(QString());
        password_lineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201", nullptr));
        captcha_label->setText(QCoreApplication::translate("LoginWindow", "\351\252\214\350\257\201\347\240\201", nullptr));
        captcha_lineEdit->setText(QString());
        captcha_lineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\345\217\263\344\276\247\345\233\276\345\275\242\351\252\214\350\257\201\347\240\201", nullptr));
        captcha_image->setText(QString());
        LoginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        Forget_password->setText(QCoreApplication::translate("LoginWindow", "\345\277\230\350\256\260\345\257\206\347\240\201/\344\270\244\346\255\245\351\252\214\350\257\201", nullptr));
        three_party_login->setText(QCoreApplication::translate("LoginWindow", "\347\254\254\344\270\211\346\226\271\345\271\263\345\217\260\347\231\273\345\275\225", nullptr));
        wechat->setText(QString());
        github->setText(QString());
        no_auth->setText(QCoreApplication::translate("LoginWindow", "\346\262\241\346\234\211\350\264\246\345\217\267\357\274\237", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
