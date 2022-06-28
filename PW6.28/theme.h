#ifndef THEME_H
#define THEME_H

#include <QWidget>

class Theme : public QWidget
{
    Q_OBJECT

public:
    Theme(QWidget *parent = 0);
    ~Theme();
};

#endif // THEME_H
