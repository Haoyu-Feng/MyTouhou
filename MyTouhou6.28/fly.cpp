#include "fly.h"

Fly::Fly()
{
    Health=0;
}

bool Fly::exist(){
    return Health;
}


int Fly::xleft(){
    return x-Width*0.3;
}

int Fly::xright(){
    return x+Width*0.3;
}

int Fly::yup(){
    return y-Height*0.3;
}

int Fly::ydown(){
    return y+Height*0.3;
}//考虑到图片裁剪，留出了边界不做判定
