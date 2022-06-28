#include "theme.h"
#include <QApplication>
#include<stage.h>
#include<mainwindow.h>
#include<QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow s;
    s.show();
    return a.exec();
}
