QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = moveAndResizeWidgets
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcontainer.cpp

HEADERS  += mainwindow.h \
    tcontainer.h

FORMS    += mainwindow.ui
