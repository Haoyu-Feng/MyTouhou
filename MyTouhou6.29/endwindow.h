#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <config.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPen>
#include <Qstring>
#include <stage.h>
#include <mainwindow.h>
#include <QSound>

class EndWindow : public QWidget
{
    Q_OBJECT
    QPushButton* EndButton[2];//0:重开；1:退出
    QLabel* EndLabel;
public:
    explicit EndWindow(int my_plane_,int diff_,QWidget *parent = 0);
    int my_plane;
    int diff;
    int now_button;
    void RetryPress();//从头开始游戏
    void QuitPress();//重新打开主菜单
    QSound* endsound;
signals:
    void QuitPressed();//返回游戏标题界面，由Stage::QuitPress()接收
    void RetryPressed();//发出信号给stage，关闭当前stage。
protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // ENDWINDOW_H
