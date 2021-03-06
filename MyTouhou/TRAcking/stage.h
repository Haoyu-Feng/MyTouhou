#ifndef STAGE_H
#define STAGE_H

#include<plane.h>
#include<config.h>
#include<movevector.h>
#include<enemy.h>
#include<QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QKeyEvent>
#include<QTimer>
#include<vector>

class Stage:public QWidget{
    Q_OBJECT
public:
    Plane Myplane;//自机
    std::vector<enemy> enemies;//敌机
    MoveVector Myvector;//自机移动向量
    QTimer Timer;//定时器
    Stage(QWidget*parent=0);
    ~Stage();
    void updateAllPos();//更新位置
    void paintEvent(QPaintEvent *pe);//绘图
    void keyPressEvent(QKeyEvent *ke);//按键
    void keyReleaseEvent(QKeyEvent *ke);//松键
    void initial();
    bool meet(Plane &p, bullet &b);
    bool meet(plane_bullet &b,enemy &p);//判定碰撞
};

#endif // STAGE_H
