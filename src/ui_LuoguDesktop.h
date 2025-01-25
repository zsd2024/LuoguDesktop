/********************************************************************************
** Form generated from reading UI file 'LuoguDesktopYGyDku.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LUOGUDESKTOPYGYDKU_H
#define LUOGUDESKTOPYGYDKU_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LuoguDesktop
{
public:
    QAction *login;
    QAction *logout;
    QAction *settings;
    QAction *exit;
    QAction *help;
    QAction *about;
    QAction *show_problem;
    QAction *article_mine;
    QAction *article_ground;
    QAction *all;
    QAction *siteaffairs;
    QAction *problem;
    QAction *academics;
    QAction *relevantaffairs;
    QAction *service;
    QAction *save_discuss;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *File;
    QMenu *Problem;
    QMenu *Discuss;
    QMenu *Help;
    QMenu *Article;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LuoguDesktop)
    {
        if (LuoguDesktop->objectName().isEmpty())
            LuoguDesktop->setObjectName(QString::fromUtf8("LuoguDesktop"));
        LuoguDesktop->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/assets/logo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        LuoguDesktop->setWindowIcon(icon);
        login = new QAction(LuoguDesktop);
        login->setObjectName(QString::fromUtf8("login"));
        logout = new QAction(LuoguDesktop);
        logout->setObjectName(QString::fromUtf8("logout"));
        settings = new QAction(LuoguDesktop);
        settings->setObjectName(QString::fromUtf8("settings"));
        exit = new QAction(LuoguDesktop);
        exit->setObjectName(QString::fromUtf8("exit"));
        help = new QAction(LuoguDesktop);
        help->setObjectName(QString::fromUtf8("help"));
        about = new QAction(LuoguDesktop);
        about->setObjectName(QString::fromUtf8("about"));
        show_problem = new QAction(LuoguDesktop);
        show_problem->setObjectName(QString::fromUtf8("show_problem"));
        article_mine = new QAction(LuoguDesktop);
        article_mine->setObjectName(QString::fromUtf8("article_mine"));
        article_ground = new QAction(LuoguDesktop);
        article_ground->setObjectName(QString::fromUtf8("article_ground"));
        all = new QAction(LuoguDesktop);
        all->setObjectName(QString::fromUtf8("all"));
        siteaffairs = new QAction(LuoguDesktop);
        siteaffairs->setObjectName(QString::fromUtf8("siteaffairs"));
        problem = new QAction(LuoguDesktop);
        problem->setObjectName(QString::fromUtf8("problem"));
        academics = new QAction(LuoguDesktop);
        academics->setObjectName(QString::fromUtf8("academics"));
        relevantaffairs = new QAction(LuoguDesktop);
        relevantaffairs->setObjectName(QString::fromUtf8("relevantaffairs"));
        service = new QAction(LuoguDesktop);
        service->setObjectName(QString::fromUtf8("service"));
        save_discuss = new QAction(LuoguDesktop);
        save_discuss->setObjectName(QString::fromUtf8("save_discuss"));
        centralwidget = new QWidget(LuoguDesktop);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LuoguDesktop->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LuoguDesktop);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        File = new QMenu(menubar);
        File->setObjectName(QString::fromUtf8("File"));
        Problem = new QMenu(menubar);
        Problem->setObjectName(QString::fromUtf8("Problem"));
        Discuss = new QMenu(menubar);
        Discuss->setObjectName(QString::fromUtf8("Discuss"));
        Help = new QMenu(menubar);
        Help->setObjectName(QString::fromUtf8("Help"));
        Article = new QMenu(menubar);
        Article->setObjectName(QString::fromUtf8("Article"));
        LuoguDesktop->setMenuBar(menubar);
        statusbar = new QStatusBar(LuoguDesktop);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LuoguDesktop->setStatusBar(statusbar);

        menubar->addAction(File->menuAction());
        menubar->addAction(Problem->menuAction());
        menubar->addAction(Discuss->menuAction());
        menubar->addAction(Article->menuAction());
        menubar->addAction(Help->menuAction());
        File->addAction(login);
        File->addAction(logout);
        File->addSeparator();
        File->addAction(settings);
        File->addAction(exit);
        Problem->addAction(show_problem);
        Discuss->addAction(all);
        Discuss->addAction(siteaffairs);
        Discuss->addAction(problem);
        Discuss->addAction(academics);
        Discuss->addAction(relevantaffairs);
        Discuss->addAction(service);
        Discuss->addSeparator();
        Discuss->addAction(save_discuss);
        Help->addAction(help);
        Help->addAction(about);
        Article->addAction(article_mine);
        Article->addAction(article_ground);

        retranslateUi(LuoguDesktop);

        QMetaObject::connectSlotsByName(LuoguDesktop);
    } // setupUi

    void retranslateUi(QMainWindow *LuoguDesktop)
    {
        LuoguDesktop->setWindowTitle(QCoreApplication::translate("LuoguDesktop", "LuoguDesktop", nullptr));
        login->setText(QCoreApplication::translate("LuoguDesktop", "\347\231\273\345\275\225", nullptr));
        logout->setText(QCoreApplication::translate("LuoguDesktop", "\347\231\273\345\207\272", nullptr));
        settings->setText(QCoreApplication::translate("LuoguDesktop", "\350\256\276\347\275\256", nullptr));
        exit->setText(QCoreApplication::translate("LuoguDesktop", "\351\200\200\345\207\272", nullptr));
        help->setText(QCoreApplication::translate("LuoguDesktop", "\345\270\256\345\212\251", nullptr));
        about->setText(QCoreApplication::translate("LuoguDesktop", "\345\205\263\344\272\216", nullptr));
        show_problem->setText(QCoreApplication::translate("LuoguDesktop", "\346\237\245\347\234\213\351\242\230\347\233\256", nullptr));
        article_mine->setText(QCoreApplication::translate("LuoguDesktop", "\346\210\221\347\232\204\344\270\223\346\240\217", nullptr));
        article_ground->setText(QCoreApplication::translate("LuoguDesktop", "\346\226\207\347\253\240\345\271\277\345\234\272", nullptr));
        all->setText(QCoreApplication::translate("LuoguDesktop", "\345\205\250\351\203\250\346\235\277\345\235\227", nullptr));
        siteaffairs->setText(QCoreApplication::translate("LuoguDesktop", "\347\253\231\345\212\241\347\211\210", nullptr));
        problem->setText(QCoreApplication::translate("LuoguDesktop", "\351\242\230\347\233\256\346\200\273\347\211\210", nullptr));
        academics->setText(QCoreApplication::translate("LuoguDesktop", "\345\255\246\346\234\257\347\211\210", nullptr));
        relevantaffairs->setText(QCoreApplication::translate("LuoguDesktop", "\347\201\214\346\260\264\345\214\272", nullptr));
        service->setText(QCoreApplication::translate("LuoguDesktop", "\345\267\245\345\215\225\345\217\215\351\246\210\347\211\210", nullptr));
        save_discuss->setText(QCoreApplication::translate("LuoguDesktop", "\344\277\235\345\255\230\345\270\226\345\255\220", nullptr));
        File->setTitle(QCoreApplication::translate("LuoguDesktop", "\346\226\207\344\273\266", nullptr));
        Problem->setTitle(QCoreApplication::translate("LuoguDesktop", "\351\242\230\347\233\256", nullptr));
        Discuss->setTitle(QCoreApplication::translate("LuoguDesktop", "\350\256\250\350\256\272", nullptr));
        Help->setTitle(QCoreApplication::translate("LuoguDesktop", "\345\270\256\345\212\251", nullptr));
        Article->setTitle(QCoreApplication::translate("LuoguDesktop", "\344\270\223\346\240\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LuoguDesktop: public Ui_LuoguDesktop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LUOGUDESKTOPYGYDKU_H
