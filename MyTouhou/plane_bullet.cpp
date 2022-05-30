#include "plane_bullet.h"

plane_bullet::plane_bullet(plane* from_pl){
    pl=from_pl;
    pic.load(":/res/zhadan.png");
    speed=10;
    x=pl->x;
    y=pl->y;
}
