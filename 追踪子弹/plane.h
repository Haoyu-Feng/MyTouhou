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
    void shoot();
    int CD;
    int nowCD;//与射击频率有关
    bool shifted;//shift切换低速并显示判定点
    plane_bullet p_b[MAX_SHOOT]={};//射击相关
    int card;//技能
    void move(int dx,int dy);
    int t_h;
    int t_w;//自机的判定点只占贴图小部分，这里单独记录贴图高、宽
};

//应该会设计不少于2位自机，这里还有修改空间


#endif // PLANE_H
