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
    mProcessType = PROCESS_TYPE::PEAK_CALLING;
    mOutputPath = QDir::currentPath() + "/" + aOutputPath;
    QString peakCallingCmd = "bash /home/thsieh/JAMM-1.0.7.3/JAMM.sh " + aCmd;
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
    mProcessType = PROCESS_TYPE::TEPIC;
    mOutputPath = "/home/thsieh/TEPIC-1.0.0/Code/" + aOutputPath;
    QDir::setCurrent( QStringLiteral("/home/thsieh/TEPIC-1.0.0/Code") );
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
    QString cmd = "";
    QStringList fileSuffix = aFilePath.split( "." );
    if( fileSuffix.at( fileSuffix.size() - 1 ) == "bed" ){
        cmd = "Rscript /home/thsieh/Epigenetic_tool/bed_detail.R " + aFilePath;
    }
    else{
        cmd = "Rscript /home/thsieh/Epigenetic_tool/peak.R " + aFilePath;
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
    mProcessType = PROCESS_TYPE::INTEGRATE_DATA;
    mOutputPath = "/home/thsieh/Epigenetic_tool/" + aOutputPath;
    QDir::setCurrent( QStringLiteral("/home/thsieh/Epigenetic_tool") );
    QString integrateCmd = "bash ./generateM.sh '\"''\"'' '\"''\"' " + aCmd + " " + aOutputPath;
    qInfo() << integrateCmd;
    mProcess->start( integrateCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ), Qt::UniqueConnection );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ), Qt::UniqueConnection );

} // end of function AnalysisManager::integrateData()
