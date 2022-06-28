#include "enemy.h"

enemy::enemy()
{
}

yousei::yousei(){Health=0;}

yousei::yousei(int x_,int y_){
    pic.load(":/res/yousei.png");
    Width=pic.width();
    Height=pic.height();
    x=x_;
    y=y_;
    Health=100;
    shoot_temp=0;
    CD=10;
    nowCD=-5;
    duration=900;
    d=0;
    for(int i=0;i<MAX_SHOOT;++i){
        e_b[i]=enemy_bullet(x,y);
    }
}

void yousei::enemy::shoot(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp++].Health=(1<<22);
    }
}

void yousei::enemy::move(){
    d++;
    if(d<duration/2){
        x+=1.0;
        y+=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i].x=x;e_b[i].y=y;
        }
    }
    else if(d<=duration){
        x+=1.0;
        y-=0.5;
        for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i].x=x;e_b[i].y=y;
        }
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void yousei::enemy::setDuration(int du){
    duration=du;
}

void yousei::enemy::move1()
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

void yousei::enemy::move2()
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
