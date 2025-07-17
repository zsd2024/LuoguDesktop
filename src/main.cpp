#include "LuoguDesktop.h"
#include "Latex/LatexToSvg.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

LuoguDesktop *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new LuoguDesktop;
    Latex latex;
    qDebug() << latex.LatexToURICode(R"(\frac{a}{b})", true);
    return a.exec();
}