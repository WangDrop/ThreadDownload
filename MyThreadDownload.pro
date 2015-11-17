#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T23:08:19
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyThreadDownload
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    downloadcontrol.cpp \
    downloadthread.cpp

HEADERS  += widget.h \
    config.h \
    downloadcontrol.h \
    downloadthread.h
