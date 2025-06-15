#include "LuoguDesktop.h"

LuoguDesktop::LuoguDesktop(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_LuoguDesktop), login(new LoginWindow)
{
    ui->setupUi(this);
    this->hide();
    connect(login, &LoginWindow::LoginSucceed, [this]()
            { show(); });
    login->show();
}

LuoguDesktop::~LuoguDesktop()
{
    delete ui;
}