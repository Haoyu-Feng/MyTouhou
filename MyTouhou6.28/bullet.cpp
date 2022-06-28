#include "bullet.h"

bullet::bullet()
{
}

plane_bullet::plane_bullet(){
    Health=0;
}

bomb::bomb(int x_, int y_){
    pic.load(":/res/Bomb.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=0;
    x=x_;
    y=y_;
    Health=(1<<22);
    attack=0;
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
    attack=3;
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
    attack=6;
}

void bullet::move(){
    if(!exist()){
        return;
    }
    x+=xspeed;
    y+=yspeed;
    if(xleft()<-Width||xright()>GM_WIDTH
            +Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void bullet::move(int xx,int yy){
    if(x-xx>1000||x-xx<-1000){
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

enemy_bullet::enemy_bullet(){
    Health=0;
}

red_small_bullet::red_small_bullet(){
    Health=0;
}

red_small_bullet::red_small_bullet(int x_,int y_){
    pic.load(":/res/red_small.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

blue_small_bullet::blue_small_bullet(){
    Health=0;
}

blue_small_bullet::blue_small_bullet(int x_,int y_){
    pic.load(":/res/blue_small.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

blue_middle_bullet::blue_middle_bullet(){
    Health=0;
}

blue_middle_bullet::blue_middle_bullet(int x_,int y_){
    pic.load(":/res/blue_middle.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

red_big_bullet::red_big_bullet(){
    Health=0;
}

red_big_bullet::red_big_bullet(int x_,int y_){
    pic.load(":/res/red_big.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

yellow_star_bullet::yellow_star_bullet(){
    Health=0;
}

yellow_star_bullet::yellow_star_bullet(int x_,int y_){
    pic.load(":/res/yellow_star.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

yellow_ellipse_bullet::yellow_ellipse_bullet(){
    Health=0;
}

yellow_ellipse_bullet::yellow_ellipse_bullet(int x_,int y_){
    pic.load(":/res/yellow_ellipse.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

orange_tri_bullet::orange_tri_bullet(){
    Health=0;
}

orange_tri_bullet::orange_tri_bullet(int x_,int y_){
    pic.load(":/res/orange_tri.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

green_sword_bullet::green_sword_bullet(){
    Health=0;
}

green_sword_bullet::green_sword_bullet(int x_,int y_){
    pic.load(":/res/green_sword.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
}

white_mi_bullet::white_mi_bullet(){
    Health=0;
}

white_mi_bullet::white_mi_bullet(int x_,int y_){
    pic.load(":/res/white_mi.png");
    Width=pic.width();
    Height=pic.height();
    xspeed=0;
    yspeed=5;
    x=x_;
    y=y_+Height*0.5;
    Health=0;
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

