#ifndef ENEMY_H
#define ENEMY_H
#include<QPixmap>
#include<config.h>
#include<bullet.h>

//把敌人也视为子弹了，毕竟撞敌人也应受损
class enemy:public bullet
{
public:
    enemy();
    enemy_bullet *e_b[MAX_SHOOT]={};//不同点
    int shoot_temp;//不同点
    int nowCD;
    int CD;//不同点
    int duration;
    int d;
    int life;
    virtual void move();//不同点
    virtual void shoot();//不同点
    void setDuration(int );
    void die();
    qreal theta;//记录move1()中圆弧转过的角度
    void move1();//一种弧线运动，从左开始
    void move2();//同上，从右开始
};

//为了方便，暂定发射弹型与敌人种类绑定
class yousei:public enemy{
public:
    yousei();
    yousei(int x_,int y_,int l_,int cd_,int h_);
    virtual void move();
    virtual void shoot();
};

class flower_yousei:public enemy{
public:
    flower_yousei();
    flower_yousei(int x_,int y_,int l_,int cd_,int h_);
    virtual void move();
    virtual void shoot();
};

class light_butterfly:public enemy{
public:
    light_butterfly();
    light_butterfly(int x_,int y_,int l_,int cd_,int h_);
};

class dark_butterfly:public enemy{
public:
    dark_butterfly();
    dark_butterfly(int x_,int y_,int l_,int cd_,int h_);
};

class mid_butterfly:public enemy{
public:
    mid_butterfly();
    mid_butterfly(int x_,int y_,int l_,int cd_,int h_);
};

class MAO:public enemy{
public:
    MAO();
    MAO(int x_,int y_,int l_,int cd_,int h_);
};

class inyo:public enemy{
public:
    inyo();
    inyo(int x_,int y_,int l_,int cd_,int h_);
};



#endif // ENEMY_H
