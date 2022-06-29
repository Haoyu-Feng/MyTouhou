#include "chooseplane.h"

ChoosePlane::ChoosePlane(QWidget *parent) : QWidget(parent)
{
    resize(GM_WIDTH,GM_HEIGHT);
    setMinimumSize(GM_WIDTH,GM_HEIGHT);
    setMaximumSize(GM_WIDTH,GM_HEIGHT);
    setAutoFillBackground(true);
    x=GM_WIDTH/2;
    y=GM_HEIGHT/2;
    now_plane=0;
    change_plane();
}

void ChoosePlane::change_plane(){
    if(now_plane==0){
        QPalette palette;
        QPixmap pixmap(":/res/plane_select_left.png");
        palette.setBrush(QPalette::Window, QBrush(pixmap));
        setPalette(palette);
    }
    else if(now_plane==1){
        QPalette palette;
        QPixmap pixmap(":/res/plane_select_right.png");
        palette.setBrush(QPalette::Window, QBrush(pixmap));
        setPalette(palette);
    }
}

void ChoosePlane::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Left:
            ke->accept();
            if(now_plane!=0){
                now_plane=0;
                change_plane();
            }
            break;
        case Qt::Key_Right:
            ke->accept();
            if(now_plane!=1){
                now_plane=1;
                change_plane();
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
