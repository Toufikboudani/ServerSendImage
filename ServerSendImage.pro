#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T08:10:23
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       -= gui
QT       += sql
QT       += xml
QT       += multimedia multimediawidgets
QT       += concurrent widgets
QT       +=network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerSendImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    File.qrc
