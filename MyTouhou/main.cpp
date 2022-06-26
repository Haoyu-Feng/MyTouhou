#include "theme.h"
#include <QApplication>
#include <stage.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
//    s.show();
    return a.exec();
}
