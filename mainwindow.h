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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addFile();
    void addBedFile();
    void peakCalling();
    void readFile( QString fileName );
    void addDirectory();
    void updateLogText( QString aStdErr, QString aStdOut );
    void closeTab( int aIndex );
    void analyzeFile();

private:
    Ui::MainWindow *mUi;
    FileListWidget *mList;
    QDockWidget *mDockLeft;
    QDockWidget *mDockRight;
    void createMenuBar();
    void createToolBar();
    void createAnalysisDock();
    void createFileListDock();
    void readJpg( QString fileName );


};

#endif // MAINWINDOW_H
