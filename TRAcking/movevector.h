#ifndef MOVEVECTOR_H
#define MOVEVECTOR_H
#include<QString>
#include<QtMath>

//实现平滑移动
class MoveVector
{
public:
    MoveVector();
    void toZeroVector();//归零
    void GenerateVector();//生成
    void movex(qreal dx);
    void movey(qreal dy);
    QString StateofMoveKeys[5];//按键状态，0~4分别对应right,up,left,down,shift
    qreal Vx;
    qreal Vy;
};

#endif // MOVEVECTOR_H
