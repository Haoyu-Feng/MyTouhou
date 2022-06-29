#include "endwindow.h"

EndWindow::EndWindow(int my_plane_,int diff_,QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    endsound=new QSound(":/res/player_score.wav");
    my_plane=my_plane_;
    diff=diff_;
    resize(PE_WIDTH,PE_HEIGHT);
    move(GM_WIDTH/4,GM_HEIGHT/5);
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());//消除边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    setAttribute(Qt::WA_DeleteOnClose,true);//设置stage界面关闭时，该界面自动关闭
    QFont font("华文中宋",20);//设置字体和大小
    EndLabel = new QLabel();
    EndLabel->setFont(font);
    EndLabel->move(PE_WIDTH/5+30,PE_HEIGHT/4);
    EndLabel->setText(tr("满身疮痍"));
    EndLabel->hide();
    for(int i=0;i<END_BUTTON_CNT;i++){
        EndButton[i] = new QPushButton(this);
        EndButton[i]->setFont(font);
        switch(i){
            case 0:
                EndButton[i]->move(PE_WIDTH/5,PE_HEIGHT/2);
                EndButton[i]->setText(tr("从头开始游戏"));
                break;
            case 1:
                EndButton[i]->move(PE_WIDTH/5,3*PE_HEIGHT/4);
                EndButton[i]->setText(tr("返回标题画面"));
                break;
            default:break;
        }
        EndButton[i]->hide();
    }
    now_button=1;
    update();
}

void EndWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QLinearGradient linearGrad;
    QFont font;
    qreal x,y;
    QString str;
    QPainterPath ltextPath;
    str=EndLabel->text();
    x=EndLabel->x();
    y=EndLabel->y();
    font=EndLabel->font();
    linearGrad.setColorAt(0,Qt::blue);
    ltextPath.addText(x,y,font,str);
    painter.setBrush(linearGrad);
    painter.drawPath(ltextPath);
    for(int i=0;i<END_BUTTON_CNT;i++){
        QPainterPath textPath;
        str=EndButton[i]->text();
        x=EndButton[i]->x();
        y=EndButton[i]->y();
        font=EndButton[i]->font();
        if(i==now_button){
            linearGrad.setColorAt(0,PE_BUTTON_LIGHT);
        }
        else{
            linearGrad.setColorAt(0,PE_BUTTON_DARK);
        }
        textPath.addText(x,y,font,str);
        painter.setBrush(linearGrad);
        painter.drawPath(textPath);
    }
}


void EndWindow::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            if(now_button>0){
                now_button--;
                update();
            }
            break;
        case Qt::Key_Down:
            ke->accept();
            if(now_button<END_BUTTON_CNT-1){
                now_button++;
                update();
            }
            break;
        case Qt::Key_Return:
            ke->accept();
            switch(now_button){
                case 0:
                    RetryPress();
                    break;
                case 1:
                    QuitPress();
                    break;
                default:break;
            }
            break;
        case Qt::Key_Escape:
            ke->accept();
            now_button=1;
            update();
            break;
        default:
            ke->ignore();
            break;
        }
}

void EndWindow::RetryPress(){
    endsound->stop();
    Stage *s = new Stage(my_plane,diff);
    s->show();
    close();
    emit RetryPressed();
}

void EndWindow::QuitPress(){
    endsound->stop();
    mainwindow* w = new mainwindow();
    w->show();
    emit QuitPressed();
}
