#ifndef FLY_H
#define FLY_H
#include<QPixmap>
#include<config.h>
#include<cmath>

class Fly
{
public:
    Fly();
    QPixmap pic;//贴图
    qreal x;//中心
    qreal y;//中心
    int xleft();
    int xright();
    int yup();
    int ydown();//这4项是判定区域边界，绘图边界需另取
    int Width;//贴图宽
    int Height;//贴图高
    int Health;//生命值
    int Power;
    bool exist();//存活，只与生命值有关
};


#endif // FLY_H
