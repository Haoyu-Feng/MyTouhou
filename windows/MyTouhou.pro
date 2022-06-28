#-------------------------------------------------
#
# Project created by QtCreator 2022-05-15T16:27:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyTouhou
TEMPLATE = app


SOURCES += main.cpp\
    plane.cpp \
    stage.cpp \
    movevector.cpp \
    bullet.cpp \
    enemy.cpp \
    fly.cpp \
    mainwindow.cpp \
    pausewindow.cpp \
    endwindow.cpp

HEADERS  += \
    plane.h \
    config.h \
    stage.h \
    movevector.h \
    bullet.h \
    enemy.h \
    fly.h \
    mainwindow.h \
    pausewindow.h \
    endwindow.h

RESOURCES += \
    res.qrc
