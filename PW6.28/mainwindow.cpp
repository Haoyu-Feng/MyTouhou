#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
    titlesound=new QSound(":/res/title.wav");
    titlesound->play();
    titlesound->setLoops(-1);
    this->grabKeyboard();
    resize(GM_WIDTH,GM_HEIGHT);
    QFont font("Arial Black",30);//设置字体和大小

    for(int i=0;i<2;i++){
        PushButton[i] = new QPushButton(this);
        PushButton[i]->move(800,50*(i+1));
        switch(i){
            case 0:
                PushButton[i]->move(3*GM_WIDTH/5,GM_HEIGHT/4);
                PushButton[i]->setText(tr("Game Start"));
                break;
            case BUTTON_CNT-1:
                PushButton[i]->move(3*GM_WIDTH/5+30,GM_HEIGHT/4+50);
                PushButton[i]->setText(tr("Quit"));
                break;
            default:break;
        }
        PushButton[i]->setFont(font);
        PushButton[i]->hide();//不显示push button本身的文字，用painter绘制
    }
    now_button=0;//开始定位在 Game Start 上面
    update();
}

void mainwindow::paintEvent(QPaintEvent *){
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

    for(int i=0;i<BUTTON_CNT;i++){
        QPainterPath textPath;
        str=PushButton[i]->text();
        x=PushButton[i]->x();
        y=PushButton[i]->y();
        font=PushButton[i]->font();
        if(i==now_button){
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

void mainwindow::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            if(now_button>0){
                now_button--;
            }
            break;
        case Qt::Key_Down:
            ke->accept();
            if(now_button<BUTTON_CNT-1){
                now_button++;
            }
            break;
        case Qt::Key_Return://ENTER键，Qt::Key_Enter为小键盘的ENTER键，原游戏中不能使用，在这里暂时不设置
            ke->accept();
            switch(now_button){
                case 0:GameStartPress();break;
                case 1:QuitPress();break;
                default:break;
            }
            break;
        case Qt::Key_Escape:
            ke->accept();
            if(now_button!=BUTTON_CNT-1){//Quit键在最后一个
                now_button=BUTTON_CNT-1;
            }
            else{
                QuitPress();
            }
            break;
        default:
            ke->ignore();
            break;
        }
    update();
}

void mainwindow::GameStartPress(){
    Stage *s = new Stage();
    titlesound->stop();
    s->show();
    this->close();
}

void mainwindow::QuitPress(){
    this->close();
}
