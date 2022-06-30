#include "pausewindow.h"

PauseWindow::PauseWindow(int my_plane_,int diff_,Stage*stg,QWidget *parent) : QWidget(parent)
{
    mainstg=stg;
    my_plane=my_plane_;
    diff=diff_;
    resize(PE_WIDTH,PE_HEIGHT);
    move(GM_WIDTH/4,GM_HEIGHT/5);
    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);//消除边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowModality(Qt::ApplicationModal);
    QFont font("华文中宋",35);//设置字体和大小
    PauseLabel = new QLabel();
    PauseLabel->setFont(font);
    PauseLabel->move(PE_WIDTH/5+55,PE_HEIGHT*0.15);
    PauseLabel->setText(tr("游戏暂停"));
    PauseLabel->hide();
    for(int i=0;i<PAUSE_BUTTON_CNT;i++){
        PauseButton[i] = new QPushButton(this);
        PauseButton[i]->setFont(font);
        switch(i){
            case 0:
                PauseButton[i]->move(PE_WIDTH/5,PE_HEIGHT/4+100);
                PauseButton[i]->setText(tr("游戏暂停解除"));
                break;
            case 1:
                PauseButton[i]->move(PE_WIDTH/5,PE_HEIGHT/2+50);
                PauseButton[i]->setText(tr("返回标题画面"));
                break;
            case 2:
                PauseButton[i]->move(PE_WIDTH/5,3*PE_HEIGHT/4);
                PauseButton[i]->setText(tr("从头开始游戏"));
                break;
            default:break;
        }
        PauseButton[i]->hide();
    }
    now_button=0;//开始定位在“游戏暂停解除”上面
    update();
}

void PauseWindow::paintEvent(QPaintEvent *){
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
    str=PauseLabel->text();
    x=PauseLabel->x();
    y=PauseLabel->y();
    font=PauseLabel->font();
    linearGrad.setColorAt(0,Qt::blue);
    ltextPath.addText(x,y,font,str);
    painter.setBrush(linearGrad);
    painter.drawPath(ltextPath);
    for(int i=0;i<PAUSE_BUTTON_CNT;i++){
        QPainterPath textPath;
        str=PauseButton[i]->text();
        x=PauseButton[i]->x();
        y=PauseButton[i]->y();
        font=PauseButton[i]->font();
        if(i==now_button){
            linearGrad.setColorAt(0,Qt::yellow);
        }
        else{
            linearGrad.setColorAt(0,Qt::white);
        }
        textPath.addText(x,y,font,str);
        painter.setBrush(linearGrad);
        painter.drawPath(textPath);
    }
}

void PauseWindow::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            if(now_button>0){
                now_button--;
            }
            break;
        case Qt::Key_Down:
            ke->accept();
            if(now_button<PAUSE_BUTTON_CNT-1){
                now_button++;
            }
            break;
        case Qt::Key_Return:
            ke->accept();
            switch(now_button){
                case 0:
                    emit ReturnPressed();
                    break;
                case 1:
                    QuitPress();
                    mainstg->stagesound->stop();
                    emit QuitPressed();
                    break;
                case 2:
                    RetryPress();
                    mainstg->stagesound->stop();
                    close();
                    emit RetryPressed();
                    break;
                default:break;
            }
            break;
        case Qt::Key_Escape:
            ke->accept();
            emit ReturnPressed();
            break;
        default:
            ke->ignore();
            break;
        }
    update();
}

void PauseWindow::RetryPress(){
    Stage *s = new Stage(my_plane,diff);
    s->show();
}

void PauseWindow::QuitPress(){
    mainwindow* w = new mainwindow();
    w->show();
}
