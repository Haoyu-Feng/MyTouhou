#ifndef PLANE_BULLET_H
#define PLANE_BULLET_H
#include<bullet.h>

class plane_bullet:public bullet
{
public:
    Plane* pl;
    plane_bullet(Plane* from_pl);
};

#endif // PLANE_BULLET_H
