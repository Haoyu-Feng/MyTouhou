#include<plane.h>
#include<config.h>
#include<iostream>
#include<fstream>

Plane::Plane(){
    pic.load(":/res/Reimu_fast.png");
    t_w=pic.width();
    t_h=pic.height();
    slow_pic.load(":/res/checkpoint_rm.png");
    Width=slow_pic.width();
    Height=slow_pic.height();
    x=GM_WIDTH*0.5;
    y=GM_HEIGHT-t_h*0.5;
    Health=10;
    shifted=false;
    shooting=false;
    card=ORI_CARDS;
    CD=10;
    nowCD=0;
    Power=10;
}

void Plane::move(int dx,int dy){
    if(x-t_w*0.5+dx>=0&&x+t_w*0.5+dx<=GM_WIDTH){
        x+=dx;
    }
    if(y-t_h*0.5+dy>=0&&y+t_w*0.5+dy<=GM_HEIGHT){
        y+=dy;
    }
}

void Plane::shoot(){
    ++nowCD;
    if(!shooting||nowCD<CD){
        return;
    }
    nowCD=0;
    for(int i=0;i<MAX_SHOOT;++i){
        if(!p_b[i].exist()){
            p_b[i]=plane_bullet(x,y);
            break;
        }
    }
}


