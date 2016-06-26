/*********************************************************************
*
*   HEADER NAME:
*       mainwindow.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filelistwidget.h"
#include <QtWidgets>
#include <string>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    explicit MainWindow
        (
        QWidget *parent = 0
        );

    ~MainWindow();

//----------------------------------------------------------------
// Slots
//----------------------------------------------------------------
private slots:
    void addFile();

    void delFile();

    void addBedFile();

    void peakCalling();

    void readFile
        (
        QString fileName
        );

    void addDirectory();

    void updateLogText
        (
        QString aLog
        );

    void closeTab
        (
        int aIndex
        );

    void analyzeFile();

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
private:
    void createMenuBar();

    void createToolBar();

    void createAnalysisDock();

    void createFileListDock();

    void readJpg
        (
        QString fileName
        );

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    Ui::MainWindow *mUi;
    FileListWidget *mList;
    QDockWidget *mDockLeft;
    QDockWidget *mDockRight;

};

#endif // MAINWINDOW_H
