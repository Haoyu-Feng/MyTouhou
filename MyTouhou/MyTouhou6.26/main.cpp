#include "theme.h"
#include <QApplication>
#include<stage.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Stage s;
    s.show();
    return a.exec();
}
