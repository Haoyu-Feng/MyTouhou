#include "bullet.h"
#include<QtMath>
bullet::bullet()
{
}

plane_bullet::plane_bullet(){
    Health=0;
}

plane_bullet::plane_bullet(int x_,int y_){
    pic.load(":/res/zhadan.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=-10;
    x=x_;
    y=y_-Height*0.5;
    Health=(1<<22);//子弹默认不会被摧毁，只会在需要消失时变为0
    attack=2;
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

/*void bullet::moverotate(const int x0,const int y0){
    if(!exist()){
        return;
    }
    int dy=yspeed;
    int dx=xspeed;
    dx=-(y/x)*dy;
    x+=dx;
    y+=yspeed;

    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}
*/

void bullet::movetrack(int xx,int yy){//追踪的目标位置
    if(!exist()){
        return;
    }
    qreal length=qSqrt((xx-x)*(xx-x)+(yy-y)*(yy-y));
    if(length<500){
    int dx=(xx-x)/10;
    //int dy=(yy-y)/100;
    x+=dx;
    y+=yspeed;
    }
    else{
        y+=yspeed;
        x+=xspeed;
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void bullet::movecross(){
    if(!exist()){
        return;
    }


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


