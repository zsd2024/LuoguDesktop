#pragma once
#include "ui_LuoguDesktop.h"
#include "Login/Login.h"
#include <QMainWindow>

class LuoguDesktop : public QMainWindow
{
    Q_OBJECT

public:
    LuoguDesktop(QWidget *parent = nullptr);
    ~LuoguDesktop();

private:
    Ui_LuoguDesktop *ui;
    LoginWindow *login;
};