#ifndef LOSEWINDOW_H
#define LOSEWINDOW_H


class LoseWindow : public QWidget
{
    Q_OBJECT
    QPushButton* LoseButton[2];//0:继续；1:退出；2:重开
    QLabel* LoseLabel;
public:
    explicit LoseWindow(QWidget *parent = 0);
    int now_button;
    void RetryPress();//从头开始游戏
    void QuitPress();//重新打开主菜单
signals:
    void ReturnPressed();//发出游戏暂停解除的信号，由Stage::ReturnPress()接收
    void QuitPressed();//返回游戏标题界面，由Stage::QuitPress()接收
    void RetryPressed();//发出信号给stage，关闭当前stage。由于把parent设为stage会出现我无法解决的bug，所以采用了现在的方式
protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // LOSEWINDOW_H
