#include "theme.h"
#include <QApplication>
#include<stage.h>
#include<mainwindow.h>
#include<choosestage.h>
#include<chooseplane.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow mw;
    mw.show();
    return a.exec();
}
