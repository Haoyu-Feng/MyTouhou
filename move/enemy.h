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
    void shoot1();//同时发射多枚子弹
    void shoot2(int xx,int yy);//瞄准，三角形
    void shoot3();//螺旋形
    int shoot_temp;
    int nowCD;
    int CD;
    int duration;
    int d;
    int shoot_num;//当前发射子弹数量
    void move();//暂时先以折线运动
    void setDuration(int );
    void die();
    qreal theta;//记录move1()中圆弧转过的角度
    void move1();//一种弧线运动，从左开始
    void move2();//同上，从右开始
    void move3();//菱形运动
};
//妖精，敌人的一种
//为了方便，暂定发射弹型与敌人种类绑定
class yousei:public enemy{
public:
    yousei();
    yousei(int x_,int y_);
};


#endif // ENEMY_H
