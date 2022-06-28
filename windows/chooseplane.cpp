#include "chooseplane.h"

ChoosePlane::ChoosePlane(QWidget *parent) : QWidget(parent)
{
    resize(GM_WIDTH,GM_HEIGHT);
    x=GM_WIDTH/2;
    y=GM_HEIGHT/2;
    now_plane=0;
    update();
}

void ChoosePlane::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pic;
    int Width;
    int Height;
    if(now_plane==0){
        pic.load(":/res/Reimu_fast.png");
        Width=pic.width();
        Height=pic.height();
    }
    else if(now_plane==1){
        pic.load(":/res/Marisa_fast.png");
        Width=pic.width();
        Height=pic.height();
    }
    painter.drawPixmap(x-Width/2,y-Height/2,pic);
}

void ChoosePlane::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Left:
            ke->accept();
            if(now_plane!=0){
                now_plane=0;
                update();
            }
            break;
        case Qt::Key_Right:
            ke->accept();
            if(now_plane!=1){
                now_plane=1;
                update();
            }
            break;
        case Qt::Key_Return:
            ke->accept();
            emit chosen();
            break;
        case Qt::Key_Escape:
            ke->accept();
            emit returned();
            break;
        default:
            ke->ignore();
            break;
        }
}
