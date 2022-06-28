#ifndef CHOOSESTAGE_H
#define CHOOSESTAGE_H

#include <QWidget>
#include <QLabel>
#include <config.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPen>
#include <QPainter>

class ChooseStage : public QWidget
{
    Q_OBJECT
    QLabel *StageButton[STAGE_CNT];
public:
    explicit ChooseStage(QWidget *parent = 0);
    int now_stage;
    void choose();
protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
signals:
    void chosen();
    void returned();
};

#endif // CHOOSESTAGE_H
