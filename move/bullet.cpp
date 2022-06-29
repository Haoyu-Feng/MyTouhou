#include "bullet.h"

bullet::bullet()
{
}

plane_bullet::plane_bullet(){
    Health=0;
}

RM_main_bullet::RM_main_bullet(){
    Health=0;
}

RM_main_bullet::RM_main_bullet(int x_,int y_){
    pic.load(":/res/Reimu_main.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=-10;
    x=x_;
    y=y_-Height*0.5;
    Health=(1<<22);//子弹默认不会被摧毁，只会在需要消失时变为0
    attack=5;
}

RM_assist_bullet::RM_assist_bullet(){
    Health=0;
}

RM_assist_bullet::RM_assist_bullet(int x_,int y_){
    pic.load(":/res/Reimu_assist.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=-10;
    x=x_;
    y=y_-Height*0.5;
    Health=(1<<22);//子弹默认不会被摧毁，只会在需要消失时变为0
    attack=2;
}

MRS_main_bullet::MRS_main_bullet(){
    Health=0;
}

MRS_main_bullet::MRS_main_bullet(int x_,int y_){
    pic.load(":/res/Marisa_main.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=-20;
    x=x_;
    y=y_-Height*0.5;
    Health=(1<<22);
    attack=6;
}

MRS_assist_bullet::MRS_assist_bullet(){
    Health=0;
}

MRS_assist_bullet::MRS_assist_bullet(int x_,int y_){
    pic.load(":/res/Marisa_assist.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=-20;
    x=x_;
    y=y_-Height*0.5;
    Health=(1<<22);
    attack=4;
}

void bullet::move(){
    if(!exist()){
        return;
    }
    x+=xspeed;
    y+=yspeed;
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void bullet::move(int xx,int yy){
    if(y-yy<-10||x-xx>500||x-xx<-500){
        move();
        return;
    }
    if(!exist()){
        return;
    }
    int dx=(xx-x)/15;
    int dy=(yy-y)/15;
    if(yspeed<dy){
        dy=yspeed;
    }
    x+=dx;
    y+=dy;
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void bullet::move(int k){
    if(!exist()){
        return;
    }
    const double v = 1.0;
    const double theta = PI/6+(k%6)*2*PI/15;
    x-=v*cos(theta);
    y+=v*sin(theta);
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void bullet::move1(int k){
    if(!exist()){
        return;
    }
    const double v = 1.0;
    const double theta = (k%15)*2*PI/15;
    x+=v*cos(theta);
    y+=v*sin(theta);
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}


enemy_bullet::enemy_bullet(){
    Health=0;
}

enemy_bullet::enemy_bullet(int x_, int y_){
    pic.load(":/res/yu.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;//需要发射时再变
    attack=2;
}

Power::Power(){
    Health=0;
}

Power::Power(int x_, int y_){
    pic.load(":/res/power.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=3;
    x=x_;
    y=y_+Height*0.5;
    Health=1;
}

