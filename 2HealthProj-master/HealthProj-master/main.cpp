#include "mainwidget.h"

#include <QApplication>
#include "Qwidgetecgcom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    //QWidgetEcgCom q;
    w.show();
    return a.exec();
}
