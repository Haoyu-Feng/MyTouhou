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
#include<QLabel>
class PauseWindow;
class EndWindow;

class Stage:public QWidget{
    Q_OBJECT
public:
    Plane1 Myplane;//自机
    std::vector<enemy> enemies;//敌机
    std::vector<Power> powers;
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
    int lifeleft;
    //下面是得分、生命、火力的内容
    //    QLabel* HiScore;//历史最高的得分，暂时不考虑
        QLabel* Score;//得分标签
        QLabel* Player;//剩余生命标签
        QLabel* Powers;//火力标签
    //    int hi_score;
        int score;
        QString player;
    PauseWindow* pw;//暂停界面
    EndWindow* ew;//结束界面
    void PausePress();//暂停
    void closeEvent(QCloseEvent *);//重写closeEvent函数，实现关闭主窗口的同时也关闭暂停界面或结束界面

public slots:
    void ReturnPress();//接收PauseWindow::ReturnPressed()的槽函数，关闭暂停界面，继续游戏
    void QuitPress();//接收PauseWindow::QuitPressed()和EndWindow::Quitpressed()的槽函数，返回到主界面
};


void endgame();

#endif // STAGE_H
