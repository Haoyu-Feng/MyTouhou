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
    CD=20;
    nowCD=-5;
    duration=900;
    d=0;
    shoot_num=0;
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
        e_b[shoot_temp].x=x;
        e_b[shoot_temp].y=y;
        e_b[shoot_temp++].Health=(1<<22);
    }
}

void yousei::enemy::shoot1(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    if((d>=duration/10&&d<2*duration/10)||(d>=3*duration/10&&d<4*duration/10)||(d>=5*duration/10&&d<6*duration/10)||(d>=7*duration/10&&d<8*duration/10)||(d>9*duration/10)){
        return;
    }
    nowCD=0;
    for(int i=0;i<30&&shoot_temp<MAX_SHOOT-1;i++){
        e_b[shoot_temp].x=x;
        e_b[shoot_temp].y=y;
        e_b[shoot_temp].xspeed=-cos((shoot_temp%15)*2*PI/15);
        e_b[shoot_temp].yspeed=sin((shoot_temp%15)*2*PI/15);
        e_b[shoot_temp++].Health=(1<<22);
    }
}

void yousei::enemy::shoot2(int xx,int yy){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    if((d>=duration/10&&d<2*duration/10)||(d>=3*duration/10&&d<4*duration/10)||(d>=5*duration/10&&d<6*duration/10)||(d>=7*duration/10&&d<8*duration/10)||(d>9*duration/10)){
        return;
    }
    nowCD=0;
    ++shoot_num;
    if(shoot_num>3){
        shoot_num=0;
    }
    if(shoot_temp+shoot_num>=MAX_SHOOT){
        return;
    }
    qreal r;
    for(int i=0;i<shoot_num;i++){
        if(shoot_num==1){
            e_b[shoot_temp].x=x;
            e_b[shoot_temp].y=y;
        }
        else if(shoot_num==2){
            if(i==0){
                e_b[shoot_temp].x=x-25;
                e_b[shoot_temp].y=y;
            }
            else if(i==1){
                e_b[shoot_temp].x=x+25;
                e_b[shoot_temp].y=y;
            }
        }
        else if(shoot_num==3){
            if(i==0){
                e_b[shoot_temp].x=x-50;
                e_b[shoot_temp].y=y;
            }
            else if(i==1){
                e_b[shoot_temp].x=x;
                e_b[shoot_temp].y=y;
            }
            else if(i==2){
                e_b[shoot_temp].x=x+50;
                e_b[shoot_temp].y=y;
            }
        }
        r=sqrt((xx-e_b[shoot_temp].x)*(xx-e_b[shoot_temp].x)+(yy-e_b[shoot_temp].y)*(yy-e_b[shoot_temp].y));
        e_b[shoot_temp].xspeed=3*(xx-e_b[shoot_temp].x)/r;
        e_b[shoot_temp].yspeed=3*(yy-e_b[shoot_temp].y)/r;
        e_b[shoot_temp++].Health=(1<<22);
    }
}

void yousei::enemy::shoot3(){
    ++nowCD;
    if(nowCD<CD){
        return;
    }
    nowCD=0;
    qreal theta;
    if(shoot_temp<MAX_SHOOT-1){
        e_b[shoot_temp].x=x;
        e_b[shoot_temp].y=y;
        theta=(shoot_temp%15)*2*PI/15;
        e_b[shoot_temp].xspeed=sin(theta);
        e_b[shoot_temp].yspeed=cos(theta);
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

void yousei::enemy::move3(){
    d++;
    if(d>=duration/10&&d<2*duration/10){
        x-=5.0;
        y+=0.8;
    }
    else if(d>=3*duration/10&&d<4*duration/10){
        x+=5.0;
        y+=0.8;
    }
    else if(d>=5*duration/10&&d<6*duration/10){
        x+=5.0;
        y-=0.8;
    }
    else if(d>=7*duration/10&&d<8*duration/10){
        x-=5.0;
        y-=0.8;
    }
    else if(d>9*duration/10){
        y-=1.0;
    }
    if(xleft()<-Width||xright()>GM_WIDTH+Width||yup()<-Height||ydown()>GM_HEIGHT+Height){
        Health=0;
    }
}
