#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T19:35:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EpigeneticsAnalysisTool
TEMPLATE = app
QT += sql widgets
QT += xml widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    filedialog.cpp \
    datamanager.cpp \
    filelistwidget.cpp \
    bedfiledata.cpp \
    analysismanager.cpp \
    peakcallingdialog.cpp \
    treewidget.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    filedialog.h \
    datamanager.h \
    filelistwidget.h \
    bedfiledata.h \
    analysismanager.h \
    peakcallingdialog.h \
    treewidget.h

FORMS    += mainwindow.ui
