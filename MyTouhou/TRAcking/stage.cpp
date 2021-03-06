#include<stage.h>

Stage::Stage(QWidget*parent):QWidget(parent){
    setAttribute(Qt::WA_DeleteOnClose,true);
    resize(GM_WIDTH,GM_HEIGHT);
    setAutoFillBackground(true);
    yousei ys1=yousei(GM_WIDTH*0.5,100);
    yousei ys2=yousei(GM_WIDTH*0.3,200);
    yousei ys3=yousei(GM_WIDTH*0.7,200);
    enemies.push_back(ys1);
    enemies.push_back(ys2);
    enemies.push_back(ys3);//debug,生成测试妖精
    Timer.setInterval(10);
    Timer.start();
    connect(&Timer,&QTimer::timeout,[=](){updateAllPos();});//定时刷新
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
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet& pb=Myplane.p_b[i];
        pb.move();//子弹移动
        //pb.moverotate();
        //pb.movetrack(); 追踪敌人的实现
        for(auto it=enemies.begin();it!=enemies.end();++it){
            enemy& ys=*it;
            if(meet(pb,ys)){
                ys.Health-=pb.attack;
                if(ys.Health<0){
                    ys.Health=0;
                }
                pb.Health=0;
            }
        }//判定子弹与敌人碰撞
    }//自机射击

    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy &ys=*it;
        ys.move();//敌机移动
        ys.shoot();
        for(int i=0;i<MAX_SHOOT;++i){
            enemy_bullet& eb=ys.e_b[i];
            eb.move();//  敌人的子弹移动*/
            //eb.movetrack(Myplane.x,Myplane.y);
            if(meet(Myplane,eb)){
                eb.Health=0;
            }
        }
    }//判断自机与敌人碰撞
    update();
}

void Stage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(Myplane.x-Myplane.t_w*0.5,Myplane.y-Myplane.t_h*0.5,Myplane.pic);//注意画图时系数0.5
    if(Myplane.shifted){
        painter.drawPixmap(Myplane.x-Myplane.Width*0.5,Myplane.y-Myplane.Height*0.5,Myplane.slow_pic);
    }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet& apb=Myplane.p_b[i];
        if(!apb.exist()){
            continue;
        }
        painter.drawPixmap(apb.x-apb.Width*0.5,apb.y-apb.Height*0.5,apb.pic);
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy &ys=*it;
        if(ys.exist()){
            painter.drawPixmap(ys.x-ys.Width*0.5,ys.y-ys.Height*0.5,ys.pic);
            for(int i=0;i<MAX_SHOOT;++i){
                enemy_bullet& aeb=ys.e_b[i];
                if(!aeb.exist()){
                    continue;
                }
                painter.drawPixmap(aeb.x-aeb.Width*0.5,aeb.y-aeb.Height*0.5,aeb.pic);
            }
        }
    }//在的都画出来
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
    if(!p.exist()||!b.exist()){
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
