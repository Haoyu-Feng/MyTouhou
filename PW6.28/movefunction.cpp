#include "bullet.h"
#include "enemy.h"




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

void bullet::move1(){//S型曲线
    if(!exist()){
        return;
    }
    timer++;
    const double v=1;
    x=cos(timer);
    y+=yspeed;
    if(yup()<-Height||ydown()>GM_HEIGHT+Height){//判定方式稍改动 可以超出水平边界
        Health=0;
    }
}
void bullet::move1(){//S型曲线
    if(!exist()){
        return;
    }
    timer++;
    const double v=1;
    x=cos(timer);
    y+=yspeed;
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
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

void enemy::move1(){// S型曲线
    d++;
    const double v=1;
    double dx=v*cos(d); //
    y+=yspeed;
    x+=dx;
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}



