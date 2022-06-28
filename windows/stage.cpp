#include<stage.h>
#include<pausewindow.h>//.h里声明 .cpp里包含头文件
#include<endwindow.h>

Stage::Stage(QWidget*parent):QWidget(parent){
    setAttribute(Qt::WA_DeleteOnClose,true);
    resize(GM_WIDTH,GM_HEIGHT);
    setAutoFillBackground(true);
    yousei ys1=yousei(GM_WIDTH*0.5,100);
    yousei ys2=yousei(GM_WIDTH*0.3,100);
    yousei ys3=yousei(GM_WIDTH*0.7,200);
    enemies.push_back(ys1);
    enemies.push_back(ys2);
    enemies.push_back(ys3);//debug,生成测试妖精
    for(int i=1;i<=300;++i){
        Power pw1=Power(GM_WIDTH*0.5,100+2*i);
        powers.push_back(pw1);
    }
    Timer.setInterval(10);
    Timer.start();
    connect(&Timer,&QTimer::timeout,[=](){updateAllPos();});//定时刷新
    lifeleft=5;
    //侧->游戏界面边栏
       score = 10;
       QFont font("Bauhaus 93",20);//华文彩云,Bauhaus 93,华文琥珀
       Score = new QLabel(this);
       Player = new QLabel(this);
       Powers = new QLabel(this);
       Score->setFont(font);
       Player->setFont(font);
       Powers->setFont(font);
       Score->setStyleSheet(LABEL_STYLE);
       Player->setStyleSheet(LABEL_STYLE);
       Powers->setStyleSheet(LABEL_STYLE);
       player = PLAYER;
       for(int i=0;i<lifeleft;i++){
           player+="★";
       }
       Score->setText(QString(SCORE).arg(score,9,10,QChar('0')));
       Player->setText(player);
       Powers->setText(QString(POWER).arg(Myplane.power/100).arg(Myplane.power%100,2,10,QChar('0')));
       Score->move(GM_WIDTH*0.7,GM_HEIGHT*0.1);
       Player->move(GM_WIDTH*0.7,GM_HEIGHT*0.15);
       Powers->move(GM_WIDTH*0.7,GM_HEIGHT*0.2);
    //暂停界面
       this->grabKeyboard();
       pw = new PauseWindow();
       pw->show();
       pw->hide();
       ew = new EndWindow();
       ew->show();
       ew->hide();
       connect(pw,&PauseWindow::ReturnPressed,this,&Stage::ReturnPress);
       connect(pw,&PauseWindow::QuitPressed,this,&Stage::QuitPress);
       connect(pw,&PauseWindow::RetryPressed,this,&Stage::close);
       connect(ew,&EndWindow::RetryPressed,this,&Stage::close);
       connect(ew,&EndWindow::QuitPressed,this,&Stage::QuitPress);
}

Stage::~Stage(){
}

void Stage::updateAllPos(){
    Myvector.GenerateVector();
    int shifted=(Myvector.StateofMoveKeys[4]==QString("pressed"))?1:0;
    int dx=qFloor(Myvector.Vx*100000.0)/(10000.0+shifted*20000.0);
    int dy=qFloor(Myvector.Vy*100000.0)/(10000.0+shifted*20000.0);//shift适当降速
    Myplane.move(dx,dy);//自机移动
    Myplane.shoot();
    if(!Myplane.exist()){
        ++Myplane.nowdeathCD;
    }
    if(Myplane.nowdeathCD==Myplane.deathCD){
        Myplane.Health=1;
        Myplane.nowdeathCD=0;
    }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* mpb=Myplane.main_bullet[i];
        mpb->move();//子弹移动
        for(auto it=enemies.begin();it!=enemies.end();++it){
            enemy& ys=*it;
            if(meet(*mpb,ys)){
                ys.Health-=mpb->attack;
                if(ys.Health<=0){
                    powers.push_back(Power(ys.x,ys.y));
                    ys.Health=0;
                }
                mpb->Health=0;
            }
        }
    }//main射击
    if(Myplane.power>=300){
        if(Myplane.name=="Reimu"){
            qreal mindis=10000;
            enemy mindisys;
            for(auto it=enemies.begin();it!=enemies.end();++it){
                if(!it->exist()){
                    continue;
                }
                enemy& ys=*it;
                qreal dis=qSqrt((ys.x-Myplane.x)*(ys.x-Myplane.x)+(ys.y-Myplane.y)*(ys.y-Myplane.y));
                if(dis<mindis) {mindisys=*it;mindis=dis;}
            }
            for(int i=0;i<MAX_SHOOT;++i){
                plane_bullet* apb=Myplane.assist_bullet[i];
                if(mindis<10000){
                    apb->move(mindisys.x+mindisys.Width*0.15,mindisys.y);//子弹移动
                }
                else{
                    apb->move();
                }
                for(auto it=enemies.begin();it!=enemies.end();++it){
                    enemy& ys=*it;
                    if(meet(*apb,ys)){
                        ys.Health-=apb->attack;
                        if(ys.Health<=0){
                            powers.push_back(Power(ys.x,ys.y));
                            ys.Health=0;
                        }
                        apb->Health=0;
                    }
                }
            }//assist射击
        }
        else{
            for(int i=0;i<MAX_SHOOT;++i){
                plane_bullet* apb=Myplane.assist_bullet[i];
                apb->move();
                for(auto it=enemies.begin();it!=enemies.end();++it){
                    enemy& ys=*it;
                    if(meet(*apb,ys)){
                        ys.Health-=apb->attack;
                        if(ys.Health<=0){
                            powers.push_back(Power(ys.x,ys.y));
                            ys.Health=0;
                        }
                        apb->Health=0;
                    }
                }
            }//assist射击
        }
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy &ys=*it;
        if(it->exist()){
            ys.move();
            ys.shoot();
        }
        for(int i=0;i<MAX_SHOOT;++i){
            enemy_bullet& eb=ys.e_b[i];
            eb.move();
            if(meet(Myplane,eb)){
                eb.Health=0;
                if(Myplane.exist()){
                    Myplane.Health=0;
                    if(lifeleft){
                        Myplane.power-=100;
                        if(Myplane.power<0){
                            Myplane.power=0;
                        }
                        --lifeleft;
                    }
                    else{
                        endgame();
                    }
                }
            }
        }
    }//判断自机与敌人碰撞
    for(auto it=powers.begin();it!=powers.end();++it){
        Power &pw=*it;
        if(it->exist()){
            pw.move();
        }
        if(meet(Myplane,pw)){
            ++score;
            if(Myplane.power<400){
                ++Myplane.power;
            }
            pw.Health=0;
        }
    }//获得power
    //侧边栏信息更新
        player = PLAYER;
        for(int i=0;i<lifeleft;i++){
            player+="★";
        }
        Score->setText(QString(SCORE).arg(score,9,10,QChar('0')));
        Player->setText(player);
        Powers->setText(QString(POWER).arg(Myplane.power/100).arg(Myplane.power%100,2,10,QChar('0')));
    update();
}

void Stage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(Myplane.nowdeathCD%2==0){
        painter.drawPixmap(Myplane.x-Myplane.t_w*0.5,Myplane.y-Myplane.t_h*0.5,Myplane.pic);//注意画图时系数0.5
        if(Myplane.shifted){
            painter.drawPixmap(Myplane.x-Myplane.Width*0.5,Myplane.y-Myplane.Height*0.5,Myplane.slow_pic);
        }
    }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* mpb=Myplane.main_bullet[i];
        if(!mpb->exist()){
            continue;
        }
        painter.drawPixmap(mpb->x-mpb->Width*0.5,mpb->y-mpb->Height*0.5,mpb->pic);
    }
    if(Myplane.power>=300){
        for(int i=0;i<MAX_SHOOT;++i){
            plane_bullet* apb=Myplane.assist_bullet[i];
            if(!apb->exist()){
                continue;
            }
            painter.drawPixmap(apb->x-apb->Width*0.5,apb->y-apb->Height*0.5,apb->pic);
        }
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy &ys=*it;
        if(ys.exist()){
            painter.drawPixmap(ys.x-ys.Width*0.5,ys.y-ys.Height*0.5,ys.pic);

        }
        for(int i=0;i<MAX_SHOOT;++i){
            enemy_bullet& aeb=ys.e_b[i];
            if(!aeb.exist()){
                continue;
            }
            painter.drawPixmap(aeb.x-aeb.Width*0.5,aeb.y-aeb.Height*0.5,aeb.pic);
        }
    }
    for(auto it=powers.begin();it!=powers.end();++it){
        Power &pw=*it;
        if(pw.exist()){
            painter.drawPixmap(pw.x-pw.Width*0.5,pw.y-pw.Height*0.5,pw.pic);
        }
    }
    //在的都画出来
}

void Stage::keyPressEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            Myvector.StateofMoveKeys[1]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_Down:
            ke->accept();
            Myvector.StateofMoveKeys[3]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_Left:
            ke->accept();
            Myvector.StateofMoveKeys[2]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_Right:
            ke->accept();
            Myvector.StateofMoveKeys[0]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_Shift:
            ke->accept();
            Myplane.shifted=true;
            Myvector.StateofMoveKeys[4]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_X:
            ke->accept();
            //Myplane.spell = true;
            break;
        case Qt::Key_Z:
            ke->accept();
            Myplane.shooting=true;
            break;
        case Qt::Key_Escape:
            ke->accept();
            PausePress();//游戏暂停
        default:
            ke->ignore();
            break;
        }
    }

void Stage::keyReleaseEvent(QKeyEvent *ke){
    switch(ke->key()){
        case Qt::Key_Up:
            ke->accept();
            Myvector.StateofMoveKeys[1]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_Down:
            ke->accept();
            Myvector.StateofMoveKeys[3]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_Left:
            ke->accept();
            Myvector.StateofMoveKeys[2]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_Right:
            ke->accept();
            Myvector.StateofMoveKeys[0]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_Shift:
            ke->accept();
            Myplane.shifted=false;
            Myvector.StateofMoveKeys[4]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_X:
            ke->accept();
            //Myplane.spell = true;
            break;
        case Qt::Key_Z:
            ke->accept();
            Myplane.shooting=false;
            break;
        default:
            ke->ignore();
            break;
        }
    }

bool Stage::meet(Plane &p, bullet &b){
    if(!b.exist()){
        return false;
    }
    bool b1=p.xleft()>b.xright();
    bool b2=b.xleft()>p.xright();
    bool b3=p.yup()>b.ydown();
    bool b4=b.yup()>p.ydown();
    return !(b1||b2||b3||b4);
}

bool Stage::meet(plane_bullet &b,enemy &p){
    if(!p.exist()||!b.exist()){
        return false;
    }
    bool b1=p.xleft()>b.xright();
    bool b2=b.xleft()>p.xright();
    bool b3=p.yup()>b.ydown();
    bool b4=b.yup()>p.ydown();
    return !(b1||b2||b3||b4);
}

void endgame(){
    return;
}

void Stage::PausePress(){
    Timer.stop();
    pw->now_button=0;
    pw->grabKeyboard();
    pw->show();
}

void Stage::ReturnPress(){
    pw->hide();
    this->grabKeyboard();
    Timer.start();
}

void Stage::QuitPress(){
    pw->close();
    this->close();
}

void Stage::closeEvent(QCloseEvent *){
    pw->close();
    if(pw)delete pw;
}
