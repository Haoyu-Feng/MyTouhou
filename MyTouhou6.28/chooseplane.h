#ifndef CHOOSEPLANE_H
#define CHOOSEPLANE_H

#include <QWidget>
#include <QPushButton>
#include <config.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>

class ChoosePlane : public QWidget
{
    Q_OBJECT
public:
    explicit ChoosePlane(QWidget *parent = 0);
    int x;
    int y;
    int now_plane;
    void change_plane();
    void choose();
protected:
    void keyPressEvent(QKeyEvent *);
    //void paintEvent(QPaintEvent *);
signals:
    void chosen();
    void returned();
};

#endif // CHOOSEPLANE_H
