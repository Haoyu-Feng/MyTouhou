#include<plane.h>
#include<config.h>
#include<iostream>
#include<fstream>

Plane::Plane(){
    Health=10;
    shifted=false;
    shooting=false;
    CD=10;
    nowCD=0;
    deathCD=200;
    nowdeathCD=0;
    power=250;
    spell=false;
    nowspellCD=0;
}

void Plane::shoot(){
;
}

void Plane::move(int dx,int dy){
    if(x-t_w*0.5+dx*movespeed>=0&&x+t_w*0.5+dx*movespeed<=GM_WIDTH){
        x+=dx*movespeed;
    }
    if(y-t_h*0.5+dy*movespeed>=0&&y+t_w*0.5+dy*movespeed<=GM_HEIGHT){
        y+=dy*movespeed;
    }
}

void Plane0::shoot(){
    ++nowCD;
    if(!shooting||nowCD<CD){
        return;
    }
    nowCD=0;
    for(int i=0;i<MAX_SHOOT;++i){
        if(!main_bullet[i]->exist()){
            main_bullet[i]=new RM_main_bullet(x,y);
            break;
        }
    }
    if(power>=300){
    for(int i=0;i<MAX_SHOOT;++i){
        if(!assist_bullet[i]->exist()){
            assist_bullet[i]=new RM_assist_bullet(x,y);
            break;
        }
    }
    }
}

void Plane1::shoot(){
    ++nowCD;
    if(!shooting||nowCD<CD){
        return;
    }
    nowCD=0;
    for(int i=0;i<MAX_SHOOT;++i){
        if(!main_bullet[i]->exist()){
            main_bullet[i]=new MRS_main_bullet(x,y);
            break;
        }
    }
    if(power>=300){
    for(int i=0;i<MAX_SHOOT;++i){
        if(!assist_bullet[i]->exist()){
            assist_bullet[i]=new MRS_assist_bullet(x,y);
            break;
        }
    }
    }
}

Plane0::Plane0(){
    pic.load(":/res/Reimu_fast.png");
    t_w=pic.width();
    t_h=pic.height();
    slow_pic.load(":/res/checkpoint_rm.png");
    Width=slow_pic.width();
    Height=slow_pic.height();
    movespeed=1;
    x=GM_WIDTH*0.5;
    y=GM_HEIGHT-t_h*0.5;
    name="Reimu";
    spellCD=100;
    for(int i=0;i<MAX_SHOOT;++i){
        main_bullet[i]=new RM_main_bullet();
    }
    for(int i=0;i<MAX_SHOOT;++i){
        assist_bullet[i]=new RM_assist_bullet();
    }
}

Plane1::Plane1(){
    pic.load(":/res/Marisa_fast.png");
    t_w=pic.width();
    t_h=pic.height();
    slow_pic.load(":/res/checkpoint_mrs.png");
    Width=slow_pic.width();
    Height=slow_pic.height();
    movespeed=1.6;
    x=GM_WIDTH*0.5;
    y=GM_HEIGHT-t_h*0.5;
    name="Marisa";
    spellCD=100;
    for(int i=0;i<MAX_SHOOT;++i){
        main_bullet[i]=new MRS_main_bullet();
    }
    for(int i=0;i<MAX_SHOOT;++i){
        assist_bullet[i]=new MRS_assist_bullet();
    }
}

