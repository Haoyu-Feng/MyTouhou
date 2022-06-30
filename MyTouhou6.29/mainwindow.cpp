#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{

    titlesound=new QSound(":/res/title.wav");
    titlesound->play();
    titlesound->setLoops(-1);
    this->grabKeyboard();
    resize(GM_WIDTH,GM_HEIGHT);

    setMinimumSize(GM_WIDTH,GM_HEIGHT);
    setMaximumSize(GM_WIDTH,GM_HEIGHT);
    setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/res/title1.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);

    QFont font("Arial Black",40);//设置字体和大小

    for(int i=0;i<2;i++){
        PushButton[i] = new QPushButton(this);
        PushButton[i]->move(800,50*(i+1));
        switch(i){
            case 0:
                PushButton[i]->move(3*GM_WIDTH/5,GM_HEIGHT/3);
                PushButton[i]->setText(tr("Game Start"));
                break;
            case BUTTON_CNT-1:
                PushButton[i]->move(3*GM_WIDTH/5+30,GM_HEIGHT/2);
                PushButton[i]->setText(tr("Quit"));
                break;
            default:break;
        }
        PushButton[i]->setFont(font);
        PushButton[i]->hide();//不显示push button本身的文字，用painter绘制
    }
    now_button=0;//开始定位在 Game Start 上面

    cs = new ChooseStage();
    cp = new ChoosePlane();
    connect(cs,&ChooseStage::chosen,this,&mainwindow::cs2cp);
    connect(cp,&ChoosePlane::chosen,this,&mainwindow::StartGame);
    connect(cp,&ChoosePlane::returned,this,&mainwindow::cp2cs);
    connect(cs,&ChooseStage::returned,this,&mainwindow::cs2main);

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
            linearGrad.setColorAt(0,"#d3d3d3");
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
    cs->show();
    cs->grabKeyboard();
    this->hide();
}

void mainwindow::QuitPress(){
    this->close();
}

void mainwindow::cs2cp(){
    cs->hide();
    cp->grabKeyboard();
    cp->show();
}

void mainwindow::cp2cs(){
    cp->hide();
    cs->grabKeyboard();
    cs->show();
}

void mainwindow::cs2main(){
    cs->hide();
    this->grabKeyboard();
    this->show();
}


void mainwindow::StartGame(){
    Stage *s = new Stage(cp->now_plane,cs->now_stage);
    titlesound->stop();    
    cs->close();
    cp->close();
    this->close();
    s->show();
}

