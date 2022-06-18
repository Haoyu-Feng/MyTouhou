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
    xspeed=0;
    yspeed=1;
    Health=100;
    shoot_temp=0;
    CD=10;
    nowCD=-5;
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
    e_b[shoot_temp].x=x;
    e_b[shoot_temp].y=y;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp++].Health=(1<<22);
    }
}

