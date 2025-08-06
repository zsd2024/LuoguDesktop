#include "LuoguDesktop.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

LuoguDesktop *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new LuoguDesktop;
    return a.exec();
}