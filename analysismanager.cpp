#include "analysismanager.h"
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include "datamanager.h"

using namespace std;

AnalysisManager* AnalysisManager::sAnalysisManager = NULL;

AnalysisManager::AnalysisManager() : QObject()
{
    cout << "AnalysisManager()" << endl;
}

AnalysisManager::~AnalysisManager()
{

}

AnalysisManager* AnalysisManager::getAnalysisManager()
{
    if( sAnalysisManager == NULL ){
        sAnalysisManager = new AnalysisManager();
    }
    return sAnalysisManager;
}

void AnalysisManager::peakCalling( QString aSampleDirectory, QString aGenomeFile, QString aOutputPath )
{
    mProcess = new QProcess();
    mOutputPath = aOutputPath;
    QString peakCallingCmd = "bash /home/thsieh/JAMM-1.0.7.3/JAMM.sh -s " + aSampleDirectory + " -g " + aGenomeFile + " -o " + aOutputPath;
    cout << peakCallingCmd.toStdString() << endl;
    mProcess->start( peakCallingCmd );
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ) );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ) );
    //connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), mDialog, SLOT( receiveFinished( int, QProcess::ExitStatus ) ) );
}

void AnalysisManager::updateText()
{
    QString stdErr = mProcess->readAllStandardError();
    QString stdOut = mProcess->readAllStandardOutput();
    mUpdateLog( stdOut, stdErr );
}

void AnalysisManager::receiveFinished(int aCode, QProcess::ExitStatus aStatus)
{
    qInfo() << "AnalysisManager::receiveFinished";
    mProcessOutputDone( mOutputPath );
}

void AnalysisManager::analyseBedFile( QString aFilePath ){
    mProcess = new QProcess();
    QString cmd = "Rscript /home/thsieh/Epigenetic_tool/bed_detail.R " + aFilePath;
    QStringList path = aFilePath.split("/");
    QString name = "analysis_" + path[ path.length() - 1 ];
    mOutputPath = QDir::currentPath() + '/' + name;
    cout << mOutputPath.toStdString() << endl;
    mProcess->start(cmd);
    connect( mProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( updateText() ) );
    connect( mProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( receiveFinished( int, QProcess::ExitStatus ) ) );
}
