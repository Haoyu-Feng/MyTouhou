#include "choosestage.h"

ChooseStage::ChooseStage(QWidget *parent) : QWidget(parent)
{
    resize(GM_WIDTH,GM_HEIGHT);
    QFont font("Arial Black",30);//设置字体和大小
    for(int i=0;i<2;i++){
        StageButton[i] = new QLabel(this);
        StageButton[i]->move(800,50*(i+1));
        switch(i){
            case 0:
                StageButton[i]->move(GM_WIDTH/2,GM_HEIGHT/3);
                StageButton[i]->setText(tr("Stage1"));
                break;
            case STAGE_CNT-1:
                StageButton[i]->move(GM_WIDTH/2,GM_HEIGHT/2);
                StageButton[i]->setText(tr("Stage2"));
                break;
            default:break;
        }
        StageButton[i]->setFont(font);
        StageButton[i]->hide();
    }
    now_stage=0;
    update();
}

void ChooseStage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QLinearGradient linearGrad;
    QFont font;
    qreal x,y;
    QString str;
    for(int i=0;i<STAGE_CNT;i++){
        QPainterPath textPath;
        str=StageButton[i]->text();
        x=StageButton[i]->x();
        y=StageButton[i]->y();
        font=StageButton[i]->font();
        if(i==now_stage){
            linearGrad.setColorAt(0,BUTTON_LIGHT);
        }
        else{
            linearGrad.setColorAt(0,BUTTON_DARK);
        }
        textPath.addText(x,y,font,str);
        painter.setBrush(linearGrad);
        painter.drawPath(textPath);
    }
}

void ChooseStage::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            if(now_stage>0){
                now_stage--;
                update();
            }
            break;
        case Qt::Key_Down:
            ke->accept();
            if(now_stage<STAGE_CNT-1){
                now_stage++;
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
