#ifndef PLANE_H
#define PLANE_H
#include<QPixmap>
#include<bullet.h>

//自机

class Plane:public Fly{
public:
    Plane();
    QPixmap slow_pic;//低速贴图
    bool shooting;
    virtual void shoot();
    int CD;
    int nowCD;//与射击频率有关
    bool shifted;//shift切换低速并显示判定点
    int card;//技能
    void move(int dx,int dy);
    int t_h;
    int t_w;//自机的判定点只占贴图小部分，这里单独记录贴图高、宽
    plane_bullet* main_bullet[MAX_SHOOT];
    plane_bullet* assist_bullet[MAX_SHOOT]={};
    int deathCD;//与子弹碰撞间隔
    int nowdeathCD;
    int movespeed;//控制移速
    int power;
};

class Plane0:public Plane{
public:
    Plane0();
    virtual void shoot();
};

class Plane1:public Plane{
public:
    Plane1();
    virtual void shoot();
};


//2位自机

#endif // PLANE_H
