#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <config.h>

class PlayerData : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerData(QWidget *parent = 0);

private:
    QSqlDatabase database;
//    QLabel* title;
    QLabel* labels[10];

};

#endif // PLAYERDATA_H
