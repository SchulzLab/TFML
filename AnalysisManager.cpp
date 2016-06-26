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
    cout << "AnalysisManager()" << endl;
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
    mOutputPath = aOutputPath;
    QString peakCallingCmd = "bash /home/thsieh/JAMM-1.0.7.3/JAMM.sh " + aCmd;
    cout << peakCallingCmd.toStdString() << endl;
    mProcess->start( peakCallingCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ) );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ) );

} // end of function AnalysisManager::peakCalling()

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
    qInfo() << "AnalysisManager::receiveFinished";
    mProcessOutputDone( mOutputPath );
} // end of function AnalysisManager::recieveFinished()

//---------------------------------------------------------------------------------
//! Execute analysis of bed file
//---------------------------------------------------------------------------------
void AnalysisManager::analyseBedFile
    (
    QString aFilePath
    )
{
    QString cmd = "Rscript /home/thsieh/Epigenetic_tool/bed_detail.R " + aFilePath;
    QStringList path = aFilePath.split( "/" );
    QString name = "analysis_" + path[ path.length() - 1 ];
    mOutputPath = QDir::currentPath() + '/' + name;
    cout << mOutputPath.toStdString() << endl;
    mProcess->start( cmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ) );
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
