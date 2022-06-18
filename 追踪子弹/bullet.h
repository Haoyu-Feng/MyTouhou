#ifndef BULLET_H
#define BULLET_H

#include<fly.h>

class bullet:public Fly
{
public:
    bullet();
    int xspeed;
    int yspeed;//这两项是暂时处理直线运动用的
    int attack;//攻击力
    void move();//有极大的改动空间！！！还需研究更一般的轨迹运动
    void moverotate();//新增加的螺旋子弹
    void movetrack(int xx,int yy);//新增加的追踪子弹
};

class plane_bullet:public bullet
{
public:
    plane_bullet();
    plane_bullet(int x_,int y_);
};

class enemy_bullet:public bullet{
public:
    enemy_bullet();
    enemy_bullet(int x_,int y_);
};

#endif // BULLET_H
