#include "LuoguDesktop.h"

LuoguDesktop::LuoguDesktop(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_LuoguDesktop)
{
    ui->setupUi(this);
}

LuoguDesktop::~LuoguDesktop()
{
    delete ui; 
}