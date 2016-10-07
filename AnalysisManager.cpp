/*********************************************************************
*
*   MODULE NAME:
*       AnalysisManager.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "AnalysisManager.hpp"
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include "DataManager.hpp"

using namespace std;

AnalysisManager* AnalysisManager::sAnalysisManager = NULL;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
AnalysisManager::AnalysisManager() : QObject()
{
    mProcess = new QProcess();
} // end of function AnalysisManager::AnalysisManager()

//---------------------------------------------------------------------------------
//! Destructor
//---------------------------------------------------------------------------------
AnalysisManager::~AnalysisManager()
{

} // end of function AnalysisManager::~AnalysisManager()

//---------------------------------------------------------------------------------
//! Get analysis manager
//---------------------------------------------------------------------------------
AnalysisManager* AnalysisManager::getAnalysisManager()
{
    if( sAnalysisManager == NULL ){
        sAnalysisManager = new AnalysisManager();
    }
    return sAnalysisManager;
} // end of function AnalysisManager::getAnalysisManager()

//---------------------------------------------------------------------------------
//! Execute peak calling
//---------------------------------------------------------------------------------
void AnalysisManager::peakCalling
    (
    QString aCmd,
    QString aOutputPath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    mProcessType = PROCESS_TYPE::PEAK_CALLING;
    mOutputPath = QDir::currentPath() + "/" + aOutputPath;
    QString file = QDir::homePath() + '/JAMM-1.0.7.3/JAMM.sh';
    QString peakCallingCmd = "bash " + file + " " + aCmd;
    cout << peakCallingCmd.toStdString() << endl;
    mProcess->start( peakCallingCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::peakCalling()

//---------------------------------------------------------------------------------
//! Execute tepic
//---------------------------------------------------------------------------------
void AnalysisManager::tepic
    (
    QString aCmd,
    QString aOutputPath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    mProcessType = PROCESS_TYPE::TEPIC;
    mOutputPath = QDir::homePath() + "/TEPIC-1.0.0/Code/" + aOutputPath;
    QString path = QDir::homePath() + "/TEPIC-1.0.0/Code";
    QDir::setCurrent( path );
    QString tepicCmd = "bash TEPIC.sh " + aCmd;
    mProcess->start( tepicCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::tepic()

//---------------------------------------------------------------------------------
//! Send signal to  the log widget in mainwindow to update log
//---------------------------------------------------------------------------------
void AnalysisManager::updateText()
{
    QString stdErr = mProcess->readAllStandardError();
    QString stdOut = mProcess->readAllStandardOutput();

    mUpdateLog( stdOut );
    mUpdateLog( stdErr );

} // end of function AnalysisManager::updateText()

//---------------------------------------------------------------------------------
//! Receive  finished event and send output done signal to notify output path
//---------------------------------------------------------------------------------
void AnalysisManager::receiveFinished
    (
    int aCode,
    QProcess::ExitStatus aStatus
    )
{
    QString outputPath;
    outputPath = DataManager::getDataManager()->moveDir( mOutputPath, mProcessType );
    mProcessOutputDone( outputPath );
    DataManager::getDataManager()->addResultPath( outputPath );

} // end of function AnalysisManager::recieveFinished()

//---------------------------------------------------------------------------------
//! Execute analysis of bed file
//---------------------------------------------------------------------------------
void AnalysisManager::analyseBedFile
    (
    QString aFilePath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    QString cmd = "";
    QStringList fileSuffix = aFilePath.split( "." );
    if( fileSuffix.at( fileSuffix.size() - 1 ) == "bed" ){
        QString file = QDir::homePath() + "/EpigeneticsTools/bed_detail.R";
        cmd = "Rscript " + file + " " + aFilePath;
    }
    else{
        QString file = QDir::homePath() + "/EpigeneticsTools/peak.R";
        cmd = "Rscript " + file + " " + aFilePath;
    }
    QStringList path = aFilePath.split( "/" );
    QString name = "analysis_" + path[ path.length() - 1 ];
    mOutputPath = QDir::currentPath() + '/' + name;
    mProcess->start( cmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );
} // end of function AnalysisManager::analyzeBedFile()

//---------------------------------------------------------------------------------
//! Stop process
//---------------------------------------------------------------------------------
void AnalysisManager::killProcess()
{
    if( mProcess != NULL && mProcess->state() != QProcess::NotRunning ){
        mProcess->kill();
        mUpdateLog( "Process killed" );
    }

} // end of function AnalysisManager::killProcess()

//---------------------------------------------------------------------------------
//! Execute integrate data
//---------------------------------------------------------------------------------
void AnalysisManager::integrateData
    (
    QString aCmd,
    QString aOutputPath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    mProcessType = PROCESS_TYPE::INTEGRATE_DATA;
    mOutputPath = QDir::homePath() + "/EpigeneticsTools/" + aOutputPath;
    QString path = QDir::homePath() + "/EpigeneticsTools";
    QDir::setCurrent( path );
    QString integrateCmd = "bash ./generateM.sh '\"''\"'' '\"''\"' " + aCmd + " " + aOutputPath;
    qInfo() << integrateCmd;
    mProcess->start( integrateCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::integrateData()

//---------------------------------------------------------------------------------
//! Execute diff learning
//---------------------------------------------------------------------------------
void AnalysisManager::diffLearning
    (
    QString aCmd,
    QString aOutputPath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    mProcessType = PROCESS_TYPE::DIFF_LEARNING;
    mOutputPath = QDir::homePath() + "/EpigeneticsTools/" + aOutputPath;
    QString path = QDir::homePath() + "/EpigeneticsTools";
    QDir::setCurrent( path );
    QString cmd = "Rscript diffLearning.R " + aCmd;
    qInfo() << cmd;
    mProcess->start( cmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::diffLearning()

//---------------------------------------------------------------------------------
//! Execute regression
//---------------------------------------------------------------------------------
void AnalysisManager::regression
    (
    QString aCmd,
    QString aOutputPath
    )
{
    if( isProcessRunning() ){
        mProcessRunning( cProcessRunning );
        return;
    }
    mProcessType = PROCESS_TYPE::REGRESSION;
    mOutputPath = QDir::homePath() + "/EpigeneticsTools/" + aOutputPath;
    QString path = QDir::homePath() + "/EpigeneticsTools";
    QDir::setCurrent( path );
    QString cmd = "Rscript regression.R " + aCmd;
    qInfo() << cmd;
    mProcess->start( cmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::regression()

//---------------------------------------------------------------------------------
//! Check if process is running
//---------------------------------------------------------------------------------
bool AnalysisManager::isProcessRunning()
{
    bool result = false;
    if( mProcess->state() == QProcess::Running ){
        result = true;
    }
    return result;
} // end of function AnalysisManager::isProcessRunning()
