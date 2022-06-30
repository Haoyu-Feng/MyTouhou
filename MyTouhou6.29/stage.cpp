#include<stage.h>

void Stage::create_enemy(){
    int r=rand()%7,x=rand()%1560+180,y=rand()%(500+difficulty*50)+50,l=rand()%3000+1000*difficulty,cd=rand()%(180-40*difficulty)+30,h=rand()%40+20*difficulty;
    switch(r){
    case 0:{
        yousei*e=new yousei(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 1:{
        flower_yousei*e=new flower_yousei(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 2:{
        light_butterfly*e=new light_butterfly(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 3:{
        dark_butterfly*e=new dark_butterfly(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 4:{
        mid_butterfly*e=new mid_butterfly(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 5:{
        MAO*e=new MAO(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    case 6:{
        inyo*e=new inyo(x,y,l,cd,h);
        enemies.push_back(e);
        break;
    }
    default:break;
}
}

Stage::Stage(int my_plane,int diff_,QWidget*parent):QWidget(parent){
    /*
    stage间主要有以下区别：
    Plane
    music
    pixmap
    vector<enemies*>:考虑提前制作完毕若干固定关卡，并按顺序生成enemy&&bullet；或随机生成,rouge_like(尽量控制可玩性
    */    
    this->grabKeyboard();
    if(my_plane==0){
        planenum=0;
        Myplane=new Plane0();
    }
    else{
        planenum=1;
        Myplane=new Plane1();
    }
    difficulty=diff_;
    srand((unsigned)time(NULL));
    setAttribute(Qt::WA_DeleteOnClose,true);
    resize(GM_WIDTH,GM_HEIGHT);
    setMinimumSize(GM_WIDTH,GM_HEIGHT);
    setMaximumSize(GM_WIDTH,GM_HEIGHT);
    setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/res/stg4bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
    stagesound=new QSound(":/res/st1201.wav");
    stagesound->play();
    stagesound->setLoops(-1);
    /*mid_butterfly* ys1=new mid_butterfly(GM_WIDTH*0.5,100);
    light_butterfly* ys2=new light_butterfly(GM_WIDTH*0.3,100);
    dark_butterfly* ys3=new dark_butterfly(GM_WIDTH*0.7,200);
    enemies.push_back(ys1);
    enemies.push_back(ys2);
    enemies.push_back(ys3);//debug,生成测试妖精*/
    enemynowCD=0;
    enemyCD=100;
    for(int i=1;i<=3*difficulty;++i){
        create_enemy();
    }
    /*for(int i=1;i<=300;++i){
    Power pw1=Power(GM_WIDTH*0.5,100+2*i);
    powers.push_back(pw1);
    }*/
    Timer.setInterval(10);
    Timer.start();
    connect(&Timer,&QTimer::timeout,[=](){updateAllPos();});//定时刷新
    lifeleft=3;
    //侧->游戏界面边栏
       score = 0;
       QFont font("Bauhaus 93",25);//华文彩云,Bauhaus 93,华文琥珀
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
       for(int i=0;i<5;i++){
           player+="★";
       }
       Score->setText(QString(SCORE).arg(score,9,10,QChar('0')));
       Player->setText(player);
       Powers->setText(QString(POWER).arg(Myplane->power/100).arg(Myplane->power%100,2,10,QChar('0')));
       Score->move(GM_WIDTH*0.75,GM_HEIGHT*0.15);
       Player->move(GM_WIDTH*0.75,GM_HEIGHT*0.2);
       Powers->move(GM_WIDTH*0.75,GM_HEIGHT*0.25);

       this->grabKeyboard();
       pw = new PauseWindow(planenum,difficulty,this);
       ew = new EndWindow(planenum,difficulty);
       //ew->endsound->stop();
       connect(pw,&PauseWindow::ReturnPressed,this,&Stage::ReturnPress);
       connect(pw,&PauseWindow::QuitPressed,this,&Stage::QuitPress);
       connect(pw,&PauseWindow::RetryPressed,this,&Stage::close);
       connect(ew,&EndWindow::RetryPressed,this,&Stage::close);
       connect(ew,&EndWindow::QuitPressed,this,&Stage::QuitPress);
}

Stage::~Stage(){
}

void Stage::updateAllPos(){
    ++enemynowCD;
    if(enemynowCD==enemyCD){
        create_enemy();
        enemynowCD=0;
    }
    Myvector.GenerateVector();
    int shifted=(Myvector.StateofMoveKeys[4]==QString("pressed"))?1:0;
    int dx=qFloor(Myvector.Vx*100000.0)/(10000.0+shifted*20000.0);
    int dy=qFloor(Myvector.Vy*100000.0)/(10000.0+shifted*20000.0);//shift适当降速
    Myplane->move(dx,dy);//自机移动
    if(Myplane->y<360){
        for(auto it=powers.begin();it!=powers.end();++it){
            Power &pw=*it;
            if(it->exist()){
                pw.move(Myplane->x,Myplane->y);
            }
        }//吸收power
    }
    if(Myplane->spell){
        Myplane->spellcard=new bomb(Myplane->x,Myplane->y);
        ++Myplane->nowspellCD;
        for(auto it=enemies.begin();it!=enemies.end();++it){
                if(!(*it)->exist()){
                    continue;
                   }
                if(meet(*Myplane->spellcard,*(*it))){
                    (*it)->Health=0;
                }
                for(int i=0;i<MAX_SHOOT;++i){
                    enemy_bullet* eb=(*it)->e_b[i];
                    if(meet(*Myplane->spellcard,*eb)){
                        eb->Health=0;
                    }
                }
    }
        }
    if(Myplane->nowspellCD==Myplane->spellCD){
        Myplane->nowspellCD=0;
        Myplane->spell=0;
    }
    Myplane->shoot();
    if(!Myplane->exist()){
        ++Myplane->nowdeathCD;
    }
    if(Myplane->nowdeathCD==Myplane->deathCD){
        Myplane->Health=1;
        Myplane->nowdeathCD=0;
    }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* mpb=Myplane->main_bullet[i];
        mpb->move();//子弹移动
        for(auto it=enemies.begin();it!=enemies.end();++it){
            enemy* ys=*it;
            if(meet(*mpb,*ys)){
                ys->Health-=mpb->attack;
                if(ys->Health<=0){
                    powers.push_back(Power(ys->x,ys->y));
                    ys->Health=0;
                }
                mpb->Health=0;
            }
        }
    }//main射击
    if(Myplane->power>=300){
        if(Myplane->name=="Reimu"){
    qreal mindis=50000;
    enemy* mindisys=NULL;
    for(auto it=enemies.begin();it!=enemies.end();++it){
            if(!(*it)->exist()){
                continue;
            }
            enemy* ys=*it;
            qreal dis=qSqrt((ys->x-Myplane->x)*(ys->x-Myplane->x)+(ys->y-Myplane->y)*(ys->y-Myplane->y));
            if(dis<mindis) {mindisys=*it;mindis=dis;}
        }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* apb=Myplane->assist_bullet[i];
        if(mindis<50000){
        apb->move(mindisys->x+mindisys->Width*0.15,mindisys->y);//子弹移动
        }
        else{
            apb->move();
        }
        for(auto it=enemies.begin();it!=enemies.end();++it){
            enemy* ys=*it;
            if(meet(*apb,*ys)){
                ys->Health-=apb->attack;
                if(ys->Health<=0){
                    powers.push_back(Power(ys->x,ys->y));
                    ys->Health=0;
                }
                apb->Health=0;
            }
        }
    }//assist射击
        }
        else{
            for(int i=0;i<MAX_SHOOT;++i){
                plane_bullet* apb=Myplane->assist_bullet[i];
                apb->move();
                for(auto it=enemies.begin();it!=enemies.end();++it){
                    enemy* ys=*it;
                    if(meet(*apb,*ys)){
                        ys->Health-=apb->attack;
                        if(ys->Health<=0){
                            powers.push_back(Power(ys->x,ys->y));
                            ys->Health=0;
                        }
                        apb->Health=0;
                    }
                }
            }//assist射击
        }
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy *ys=*it;
        if((*it)->exist()){
            ys->move();
            ys->shoot();
        }
        for(int i=0;i<MAX_SHOOT;++i){
            enemy_bullet* eb=ys->e_b[i];
            eb->move();
            if(meet(*Myplane,*eb)){
                eb->Health=0;
                if(Myplane->exist()){
                    Myplane->Health=0;
                    if(lifeleft){
                        Myplane->power-=100;
                        if(Myplane->power<0){
                            Myplane->power=0;
                        }
                        --lifeleft;
                    }
                    else{
                        endgame();
                    }
                }
            }
        }
        if(meet(*Myplane,*ys)){
            if(Myplane->exist()){
                Myplane->Health=0;
                if(lifeleft){
                    Myplane->power-=100;
                    if(Myplane->power<0){
                        Myplane->power=0;
                    }
                    --lifeleft;
                }
                else{
                    endgame();
                }
            }
        }
    }//判断自机与敌人碰撞
    for(auto it=powers.begin();it!=powers.end();++it){
        Power &pw=*it;
        if(it->exist()){
            pw.move();
        }
        if(meet(*Myplane,pw)){
            ++score;
            if(Myplane->power<400){
                Myplane->power+=20;
                if(Myplane->power>400){
                Myplane->power=400;
                }
            }
            int luck=rand()%25;
            if(!luck&&lifeleft<5){
                ++lifeleft;
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
        Powers->setText(QString(POWER).arg(Myplane->power/100).arg(Myplane->power%100,2,10,QChar('0')));
    update();
}

void Stage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(Myplane->spell){
        bomb*b=Myplane->spellcard;
    painter.drawPixmap(b->x-b->Width*0.5,b->y-b->Height*0.5,b->pic);
    }
    if(Myplane->nowdeathCD%2==0){
    painter.drawPixmap(Myplane->x-Myplane->t_w*0.5,Myplane->y-Myplane->t_h*0.5,Myplane->pic);//注意画图时系数0.5
    if(Myplane->shifted){
        painter.drawPixmap(Myplane->x-Myplane->Width*0.5,Myplane->y-Myplane->Height*0.5,Myplane->slow_pic);
    }
    }
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* mpb=Myplane->main_bullet[i];
        if(!mpb->exist()){
            continue;
        }
        painter.drawPixmap(mpb->x-mpb->Width*0.5,mpb->y-mpb->Height*0.5,mpb->pic);
    }
    if(Myplane->power>=300){
    for(int i=0;i<MAX_SHOOT;++i){
        plane_bullet* apb=Myplane->assist_bullet[i];
        if(!apb->exist()){
            continue;
        }
        painter.drawPixmap(apb->x-apb->Width*0.5,apb->y-apb->Height*0.5,apb->pic);
    }
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        enemy *ys=*it;
        if(ys->exist()){
            --ys->life;
            if(!ys->life){
                ys->Health=0;
            }
            painter.drawPixmap(ys->x-ys->Width*0.5,ys->y-ys->Height*0.5,ys->pic);

        }
        for(int i=0;i<MAX_SHOOT;++i){
            enemy_bullet* aeb=ys->e_b[i];
            if(!aeb->exist()){
                continue;
            }
            painter.drawPixmap(aeb->x-aeb->Width*0.5,aeb->y-aeb->Height*0.5,aeb->pic);
        }
    }
    for(auto it=powers.begin();it!=powers.end();++it){
        Power &pw=*it;
        if(pw.exist()){
            painter.drawPixmap(pw.x-pw.Width*0.5,pw.y-pw.Height*0.5,pw.pic);
        }
    }
    //在的都画出来
    //画难度标签
       painter.setRenderHint(QPainter::Antialiasing,true);
       QLinearGradient linearGrad;
       linearGrad.setColorAt(0,Qt::black);
       QFont font = QFont("Arial",45);
       int x=GM_WIDTH*0.8,y=GM_HEIGHT*0.1;
       QString str;
       QPen pen;
       pen.setWidth(1);
       switch(difficulty){
       case 0:
           pen.setColor(Qt::green);
           str=QString(tr(" Easy "));
           break;
       case 1:
           pen.setColor("#75fdff");
           str=QString(tr("Normal"));
           break;
       case 2:
           pen.setColor("#3e38ff");
           str=QString(tr(" Hard "));
           break;
       case 3:
           pen.setColor("#ff0a78");
           str=QString(tr("Lunatic"));
           break;
       default:break;
       }
       painter.setPen(pen);
       QPainterPath textPath;
       textPath.addText(x,y,font,str);
       painter.setBrush(linearGrad);
       painter.drawPath(textPath);
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
            Myplane->shifted=true;
            Myvector.StateofMoveKeys[4]=QString("pressed");
            updateAllPos();
            break;
        case Qt::Key_X:
            ke->accept();
            if(Myplane->power>=100){
            Myplane->power-=100;
            Myplane->spell = true;
            }
            break;
        case Qt::Key_Z:
            ke->accept();
            Myplane->shooting=true;
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
            Myplane->shifted=false;
            Myvector.StateofMoveKeys[4]=QString("unpressed");
            updateAllPos();
            break;
        case Qt::Key_X:
            ke->accept();
            break;
        case Qt::Key_Z:
            ke->accept();
            Myplane->shooting=false;
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

bool Stage::meet(plane_bullet &b, enemy_bullet &p){
    if(!p.exist()||!b.exist()){
        return false;
    }
    bool b1=p.xleft()>b.xright();
    bool b2=b.xleft()>p.xright();
    bool b3=p.yup()>b.ydown();
    bool b4=b.yup()>p.ydown();
    return !(b1||b2||b3||b4);
}

void Stage::endgame(){
    stagesound->stop();
    //EndWindow *ew=new EndWindow(planenum,difficulty);
    ew->show();
    ew->endsound->play();
    ew->endsound->setLoops(-1);
    ew->grabKeyboard();
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
    ew->close();
    this->close();
}
