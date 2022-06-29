#include "enemy.h"

enemy::enemy()
{
}

void enemy::move(){
    d++;
    if(d<duration/2){
        x+=1.0;
        y+=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    }
    else if(d<=duration){
        x+=1.0;
        y-=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void enemy::shoot(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp++]->Health=(1<<22);
    }
}


yousei::yousei(){Health=0;}

yousei::yousei(int x_,int y_,int l_,int cd_,int h_){
    pic.load(":/res/yousei.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new green_sword_bullet(x,y);
    }
}

void yousei::move(){
    d++;
    if(d<duration/2){
        x+=1.0;
        y+=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    }
    else if(d<=duration){
        x+=1.0;
        y-=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void yousei::shoot(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp++]->Health=(1<<22);
    }
}


flower_yousei::flower_yousei(){
    Health=0;
}

flower_yousei::flower_yousei(int x_,int y_,int l_,int cd_,int h_){
    pic.load(":/res/flower_yousei.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new white_mi_bullet(x,y);
    }
}


void flower_yousei::move()
{
    const double v=1;
    d++;
    if(d<duration/3){
        y+=0.8;
        x+=0.1;
    }
    else if(d>=duration/3&&d<2*duration/3){
        theta+=PI/(2*duration/3);
        x+=v*sin(theta);
        y+=v*cos(theta);
    }
    else{
        x+=1.0;
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void flower_yousei::shoot(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp++]->Health=(1<<22);
    }
}


light_butterfly::light_butterfly(){
    Health=0;
}

light_butterfly::light_butterfly(int x_, int y_,int l_,int cd_,int h_){
    pic.load(":/res/light_butterfly.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new blue_middle_bullet(x,y);
    }
}

//    以下是石显杰的测试改动 
void light_butterfly::shoot(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;

    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp]->xspeed=((shoot_temp%3)-1)*3;//shoot模式 周期化改变子弹xspeed达到多方向shoot效果
        e_b[shoot_temp++]->Health=(1<<22);
    }
}


void light_butterfly::move(){     //enemy2.   周期折现运动  参数有待调整
   d++;
    int dx=5*sin(d/15);
    int dy=5*cos(d/15);
    x+=dx;
    y+=2+dy;
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}


//以上是石显杰的测试改动



dark_butterfly::dark_butterfly(){
    Health=0;
}

dark_butterfly::dark_butterfly(int x_, int y_,int l_,int cd_,int h_){
    pic.load(":/res/dark_butterfly.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new red_big_bullet(x,y);
    }
}

//一下用作测试
void dark_butterfly::shoot(){//shoot模式2    周期化改变子弹xspeed  形成扫射效果  建议应用在cd较短的对象
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;

    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp]->xspeed=5*cos(shoot_temp*10);
        e_b[shoot_temp++]->Health=(1<<22);
    }
}




mid_butterfly::mid_butterfly(){
    Health=0;
}

mid_butterfly::mid_butterfly(int x_, int y_,int l_,int cd_,int h_){
    pic.load(":/res/mid_butterfly.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new yellow_star_bullet(x,y);
    }
}

MAO::MAO(){
    Health=0;
}

MAO::MAO(int x_, int y_,int l_,int cd_,int h_){
    pic.load(":/res/MAO.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new orange_tri_bullet(x,y);
    }
}





inyo::inyo(){
    Health=0;
}

inyo::inyo(int x_, int y_,int l_,int cd_,int h_){
    pic.load(":/res/inyo.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=h_;
    shoot_temp=0;
    CD=cd_;
    nowCD=-5;
    duration=900;
    d=0;
    life=l_;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=new yellow_ellipse_bullet(x,y);
    }
}

void enemy::setDuration(int du){
    duration=du;
}

void enemy::move2()
{
    const double v=1;
    d++;
    if(d<duration/3){
        y+=0.8;
        x-=0.1;
    }
    else if(d>=duration/3&&d<2*duration/3){
        theta+=PI/(2*duration/3);
        x-=v*sin(theta);
        y+=v*cos(theta);
    }
    else{
        x-=1.0;
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

