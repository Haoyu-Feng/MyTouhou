#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <config.h>
#include <choosestage.h>
#include <chooseplane.h>
#include <stage.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPen>
#include <Qstring>
#include <QDebug>

class mainwindow : public QWidget
{
    Q_OBJECT
    QPushButton *PushButton[2];//0:Game Start; 1:Quit
public:
    explicit mainwindow(QWidget *parent = 0);
    int now_button;
    QSound* titlesound;
    int _st;//记录选择的stage
    void GameStartPress();
    void QuitPress();
    ChooseStage* cs;
    ChoosePlane* cp;

protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);//用于写字


signals:
    void chosen(int,int);
public slots:
    void cs2cp();//从关卡选择界面到人物选择界面
    void cp2cs();//从人物选择界面退回到关卡选择界面
    void cs2main();//从关卡选择界面退回到主界面
    void StartGame();//正式开始游戏
};

#endif // MAINWINDOW_H
