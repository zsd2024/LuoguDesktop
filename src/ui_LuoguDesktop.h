/********************************************************************************
** Form generated from reading UI file 'LuoguDesktopyMEDXL.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LUOGUDESKTOPYMEDXL_H
#define LUOGUDESKTOPYMEDXL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QAction *save_discuss;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *File;
    QMenu *Problem;
    QMenu *Discuss;
    QMenu *Help;
    QMenu *Article;

    void setupUi(QMainWindow *LuoguDesktop)
    {
        if (LuoguDesktop->objectName().isEmpty())
            LuoguDesktop->setObjectName("LuoguDesktop");
        LuoguDesktop->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/assets/logo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        LuoguDesktop->setWindowIcon(icon);
        login = new QAction(LuoguDesktop);
        login->setObjectName("login");
        logout = new QAction(LuoguDesktop);
        logout->setObjectName("logout");
        settings = new QAction(LuoguDesktop);
        settings->setObjectName("settings");
        exit = new QAction(LuoguDesktop);
        exit->setObjectName("exit");
        help = new QAction(LuoguDesktop);
        help->setObjectName("help");
        about = new QAction(LuoguDesktop);
        about->setObjectName("about");
        show_problem = new QAction(LuoguDesktop);
        show_problem->setObjectName("show_problem");
        article_mine = new QAction(LuoguDesktop);
        article_mine->setObjectName("article_mine");
        article_ground = new QAction(LuoguDesktop);
        article_ground->setObjectName("article_ground");
        all = new QAction(LuoguDesktop);
        all->setObjectName("all");
        siteaffairs = new QAction(LuoguDesktop);
        siteaffairs->setObjectName("siteaffairs");
        problem = new QAction(LuoguDesktop);
        problem->setObjectName("problem");
        academics = new QAction(LuoguDesktop);
        academics->setObjectName("academics");
        save_discuss = new QAction(LuoguDesktop);
        save_discuss->setObjectName("save_discuss");
        centralwidget = new QWidget(LuoguDesktop);
        centralwidget->setObjectName("centralwidget");
        LuoguDesktop->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LuoguDesktop);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        File = new QMenu(menubar);
        File->setObjectName("File");
        Problem = new QMenu(menubar);
        Problem->setObjectName("Problem");
        Discuss = new QMenu(menubar);
        Discuss->setObjectName("Discuss");
        Help = new QMenu(menubar);
        Help->setObjectName("Help");
        Article = new QMenu(menubar);
        Article->setObjectName("Article");
        LuoguDesktop->setMenuBar(menubar);

        menubar->addAction(File->menuAction());
        menubar->addAction(Problem->menuAction());
        menubar->addAction(Discuss->menuAction());
        menubar->addAction(Article->menuAction());
        menubar->addAction(Help->menuAction());
        File->addSeparator();
        File->addAction(settings);
        File->addAction(exit);
        Problem->addAction(show_problem);
        Discuss->addAction(all);
        Discuss->addAction(siteaffairs);
        Discuss->addAction(problem);
        Discuss->addAction(academics);
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
        save_discuss->setText(QCoreApplication::translate("LuoguDesktop", "\344\277\235\345\255\230\345\270\226\345\255\220", nullptr));
        File->setTitle(QCoreApplication::translate("LuoguDesktop", "\346\226\207\344\273\266\357\274\210&F\357\274\211", nullptr));
        Problem->setTitle(QCoreApplication::translate("LuoguDesktop", "\351\242\230\347\233\256\357\274\210&P\357\274\211", nullptr));
        Discuss->setTitle(QCoreApplication::translate("LuoguDesktop", "\350\256\250\350\256\272\357\274\210&D\357\274\211", nullptr));
        Help->setTitle(QCoreApplication::translate("LuoguDesktop", "\345\270\256\345\212\251\357\274\210&H\357\274\211", nullptr));
        Article->setTitle(QCoreApplication::translate("LuoguDesktop", "\344\270\223\346\240\217\357\274\210&A\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LuoguDesktop: public Ui_LuoguDesktop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LUOGUDESKTOPYMEDXL_H
