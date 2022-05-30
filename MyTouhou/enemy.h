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
    enemy_bullet e_b[MAX_SHOOT]={};
    void shoot();//有极大的改动空间！！！涉及更一般的射击造型
    int shoot_temp;
    int nowCD;
    int CD;
};
//妖精，敌人的一种
//为了方便，暂定发射弹型与敌人种类绑定
class yousei:public enemy{
public:
    yousei();
    yousei(int x_,int y_);
};

#endif // ENEMY_H
