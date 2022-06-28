#include "theme.h"
#include <QApplication>
#include<stage.h>
#include<mainwindow.h>
#include<QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow s;    
    s.setMinimumSize(GM_WIDTH,GM_HEIGHT);
    s.setMaximumSize(GM_WIDTH,GM_HEIGHT);
    s.setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/res/title.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    s.setPalette(palette);
    s.show();
    return a.exec();
}
