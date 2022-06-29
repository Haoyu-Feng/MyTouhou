#include "enemy.h"
#include"bullet.h"
#include"fly.h"
#include<QPixmap>
#include<config.h>
#include<plane.h>
#include<bullet.h>
 
void move(){     //enemy1. 圆形复合直线运动 螺旋线    参数有待调整
    d++;
    int dx=3*cos(d*5);
    x+=dx;
    y+=yspeed;
    
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void move(){     //enemy1.  圆形复合直线运动 螺旋线  同上 旋转方向变化  参数有待调整
    d++;
    int dx=3*sin(d*5);
    x+=dx;
    y+=yspeed;
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}


void move(){     //enemy2.   周期反复横跳下降 参数有待调整
    d++;
    int k=d/50;
    int dx=0;
    if(k%2){
        dx=5;
    }
    else{
        dx=-5;
    }
    x+=dx;
    y+=yspeed;
    
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}


void move(int xx,int yy){     //enemy3.   获取我方战机坐标  全局 慢速追踪
    d++;
    
    int dx=(xx-x)/50;
    int dy=(yy-y)/50;
   
    x+=dx;
    y+=dy;
    
    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}

void move(int xx,int yy){     //enemymove4.   子弹反弹  最好和扫射共用 可以加大难度  
    d++;
    xspeed=d;
    yspeed;
    x+=xpseed;
    y+=yspeed;

    if(xleft()<-Width||xright()>GM_WIDTH+Width){
        xspeed=-xspeed;
    }

    for(int i=shoot_temp;i<MAX_SHOOT;++i){
            e_b[i]->x=x;e_b[i]->y=y;
        }

    if(yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}





























void shoot(){   //shoot模式1 周期化改变子弹xspeed  达到多方向shoot效果
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;

    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp].xspeed=((shoot_temp%3)-1)*3;//shoot模式 周期化改变子弹xspeed达到多方向shoot效果
        e_b[shoot_temp++]->Health=(1<<22);
    }
}

void shoot(){//shoot模式2    周期化改变子弹xspeed  形成扫射效果  建议应用在cd较短的对象
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;

    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp]->xspeed=cos(shoot_temp/10);
        e_b[shoot_temp++]->Health=(1<<22);
    }
}


void shoot(){       /shoot模式 周期化改变子弹xspeed达到多方向shoot效果  参数可调整
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp]->xspeed=((shoot_temp%5)-2)*1;   //同样是散射 不过是五个主方向
        e_b[shoot_temp++]->Health=(1<<22);
    }
}

