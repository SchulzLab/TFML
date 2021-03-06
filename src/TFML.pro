#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T19:35:13
#
#-------------------------------------------------


TARGET = TFML
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui
QT += webenginewidgets
QT += sql widgets
QT += xml widgets

SOURCES += Main.cpp\
        MainWindow.cpp \
    DataManager.cpp \
    FileListWidget.cpp \
    BedFileData.cpp \
    AnalysisManager.cpp \
    PeakCallingDialog.cpp \
    TepicDialog.cpp \
    FileDialog.cpp \
    ProjectDialog.cpp \
    IntegrateDataDialog.cpp \
    DiffLearnDialog.cpp \
    WebPage.cpp \
    SettingManager.cpp \
    SettingDialog.cpp

HEADERS  += MainWindow.hpp \
    DataManager.hpp \
    FileListWidget.hpp \
    BedFileData.hpp \
    AnalysisManager.hpp \
    PeakCallingDialog.hpp \
    TepicDialog.hpp \
    FileDialog.hpp \
    ProjectDialog.hpp \
    IntegrateDataDialog.hpp \
    DiffLearnDialog.hpp \
    WebPage.hpp \
    SettingManager.hpp \
    SettingDialog.hpp

FORMS    += MainWindow.ui
