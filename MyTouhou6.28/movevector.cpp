#include "movevector.h"

MoveVector::MoveVector()
{
    for(int i=0;i<5;++i){
        StateofMoveKeys[i]=QString("unpressed");
    }
    toZeroVector();
}

void MoveVector::toZeroVector(){
    Vx=Vy=0;
}

void MoveVector::movex(qreal dx){
    Vx+=dx;
}

void MoveVector::movey(qreal dy){
    Vy+=dy;
}

void MoveVector::GenerateVector(){
    toZeroVector();
    if(StateofMoveKeys[0]==QString("pressed")){
        movex(1.0);
    }
    if(StateofMoveKeys[1]==QString("pressed")){
        movey(-1.0);
    }
    if(StateofMoveKeys[2]==QString("pressed")){
        movex(-1.0);
    }
    if(StateofMoveKeys[3]==QString("pressed")){
        movey(1.0);
    }
    qreal length=qSqrt(Vx*Vx+Vy*Vy);
    if(length!=qreal(0.0)){//归一至单位向量
        Vx/=length;
        Vy/=length;
    }
}
