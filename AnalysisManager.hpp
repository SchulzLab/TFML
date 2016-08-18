/*********************************************************************
*
*   HEADER NAME:
*       AnalysisManager.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class AnalysisManager : public QObject
{
    Q_OBJECT

public:
    enum PROCESS_TYPE
    {
        PEAK_CALLING = 0,
        TEPIC = 1,
        INTEGRATE_DATA = 2,
        DIFF_LEARNING = 3,
        REGRESSION = 4
    };
//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    static AnalysisManager* getAnalysisManager();

    ~AnalysisManager();

    void peakCalling
        (
        QString aCmd,
        QString aOutputPath
        );

    void tepic
        (
        QString aCmd,
        QString aOutputPath
        );

    void analyseBedFile
        (
        QString aFilePath
        );

    void integrateData
        (
        QString aCmd,
        QString aOutputPath
        );

    void diffLearning
        (
        QString aCmd,
        QString aOutputPath
        );

    void regression
        (
        QString aCmd,
        QString aOutputPath
        );

private:
    AnalysisManager();

//----------------------------------------------------------------
// Slots
//----------------------------------------------------------------
public slots:
    void updateText();

    void receiveFinished
        (
        int aCode,
        QProcess::ExitStatus aStatus
        );

    void killProcess();

//----------------------------------------------------------------
// Signals
//----------------------------------------------------------------
signals:
    void mProcessOutputDone
        (
        QString aPath
        );

    void mUpdateLog
        (
        QString aLog
        );

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QProcess *mProcess;
    QProcess *mProcessOutput;
    QMessageBox *mResultBox;
    QString mOutputPath;
    static AnalysisManager* sAnalysisManager;
    int mProcessType;

};

#endif // ANALYSISMANAGER_H
