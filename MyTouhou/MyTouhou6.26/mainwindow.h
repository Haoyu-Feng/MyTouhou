#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <config.h>
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

protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);//用于写字


signals:

public slots:
    void GameStartPress();
    void QuitPress();
};

#endif // MAINWINDOW_H
