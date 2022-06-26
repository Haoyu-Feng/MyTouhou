#include "playerdata.h"

PlayerData::PlayerData(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    QFont font("Algerian",16);
    for(int i=0;i<10;i++){
        labels[i] = new QLabel(this);
        labels[i]->setFont(font);
        labels[i]->setStyleSheet(DATA_STYLE);
    }
    database = QSqlDatabase::database("QSQLITE");
    database.setDatabaseName("PlayerData.db");
    QSqlQuery query(database);
    query.exec("create table PlayerData(ranking int primarykey,score int)");
    query.exec("insert into PlayerData value(1,10000000)");
    query.exec("insert into PlayerData value(1,9000000)");
    query.exec("insert into PlayerData value(1,8000000)");
    query.exec("insert into PlayerData value(1,7000000)");
    query.exec("insert into PlayerData value(1,6000000)");
    query.exec("insert into PlayerData value(1,5000000)");
    query.exec("insert into PlayerData value(1,4000000)");
    query.exec("insert into PlayerData value(1,3000000)");
    query.exec("insert into PlayerData value(1,2000000)");
    query.exec("insert into PlayerData value(1,1000000)");

}
