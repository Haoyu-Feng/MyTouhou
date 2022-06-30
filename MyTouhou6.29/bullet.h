#ifndef BULLET_H
#define BULLET_H

#include<fly.h>
#include<cmath>

class bullet:public Fly
{
public:
    bullet();
    int xspeed;
    int yspeed;//这两项是暂时处理直线运动用的
    int attack;//攻击力
    virtual void move();
    void move(int xx,int yy);
    int timer;
    //有极大的改动空间！！！还需研究更一般的轨迹运动
};

class plane_bullet:public bullet{
public:
    plane_bullet();
};

class bomb:public plane_bullet{
public:
    bomb(int x_,int y_);
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

class red_small_bullet:public enemy_bullet{
public:
    red_small_bullet();
    red_small_bullet(int x_,int y_);
    virtual void move();
};

class blue_small_bullet:public enemy_bullet{
public:
    blue_small_bullet();
    blue_small_bullet(int x_,int y_);
    virtual void move();
};

class blue_middle_bullet:public enemy_bullet{
public:
    blue_middle_bullet();
    blue_middle_bullet(int x_,int y_);
};

class red_big_bullet:public enemy_bullet{
public:
    red_big_bullet();
    red_big_bullet(int x_,int y_);
};

class yellow_star_bullet:public enemy_bullet{
public:
    yellow_star_bullet();
    yellow_star_bullet(int x_,int y_);
};

class yellow_ellipse_bullet:public enemy_bullet{
public:
    yellow_ellipse_bullet();
    yellow_ellipse_bullet(int x_,int y_);
};

class orange_tri_bullet:public enemy_bullet{
public:
    orange_tri_bullet();
    orange_tri_bullet(int x_,int y_);
};

class green_sword_bullet:public enemy_bullet{
public:
    green_sword_bullet();
    green_sword_bullet(int x_,int y_);
};

class white_mi_bullet:public enemy_bullet{
public:
    white_mi_bullet();
    white_mi_bullet(int x_,int y_);
    //virtual void move();
};

class Power:public bullet{
public:
    Power();
    Power(int x_,int y_);
};


#endif // BULLET_H
