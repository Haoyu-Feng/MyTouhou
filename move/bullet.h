#ifndef BULLET_H
#define BULLET_H

#include<fly.h>
#include<cmath>

class bullet:public Fly
{
public:
    bullet();
    qreal xspeed;
    qreal yspeed;//这两项是暂时处理直线运动用的
    int attack;//攻击力
    void move();
    void move(int xx,int yy);
    //有极大的改动空间！！！还需研究更一般的轨迹运动
};

class plane_bullet:public bullet{
public:
    plane_bullet();
};

class RM_main_bullet:public plane_bullet
{
public:
    RM_main_bullet();
    RM_main_bullet(int x_,int y_);
};

class RM_assist_bullet:public plane_bullet{
public:
    RM_assist_bullet();
    RM_assist_bullet(int x_,int y_);
};

class MRS_main_bullet:public plane_bullet{
public:
    MRS_main_bullet();
    MRS_main_bullet(int x_,int y_);
};

class MRS_assist_bullet:public plane_bullet{
public:
    MRS_assist_bullet();
    MRS_assist_bullet(int x_,int y_);
};

class enemy_bullet:public bullet{
public:
    enemy_bullet();
    enemy_bullet(int x_,int y_);
};

class Power:public bullet{
public:
    Power();
    Power(int x_,int y_);
};


#endif // BULLET_H
