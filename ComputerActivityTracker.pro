#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T23:26:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerActivityTracker
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
    activitymonitor.cpp \
    manager.cpp \
    activitylogger.cpp \
    activityserver.cpp

HEADERS  += \
    activitymonitor.h \
    manager.h \
    activitylogger.h \
    activityserver.h \
    common.h
