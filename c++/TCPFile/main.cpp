#include "serverwidget.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    ClientWidget cw;
    cw.show();
    w.show();
    return a.exec();
}
