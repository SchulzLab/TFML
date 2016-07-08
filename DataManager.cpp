/*********************************************************************
*
*   MODULE NAME:
*       DataManager.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include <qfileinfo.h>
#include "AnalysisManager.hpp"
#include <qfile.h>
#include <qfileinfo.h>

DataManager* DataManager::sDataManager = NULL;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
DataManager::DataManager() : QObject()
{
    cout << "DataManager()" << endl;
    fileNameList = new vector<string>();
} // end of function DataManager::DataManager()

//---------------------------------------------------------------------------------
//! Destructor
//---------------------------------------------------------------------------------
DataManager::~DataManager()
{

} // end of function DataManager::~DataManager()

//---------------------------------------------------------------------------------
//! Get data manager
//---------------------------------------------------------------------------------
DataManager* DataManager::getDataManager()
{
    if( sDataManager == NULL ){
        sDataManager = new DataManager();
    }
    return sDataManager;
} // end of function DataManager::getDataManager()

//---------------------------------------------------------------------------------
//! Check project dir and create if project dir not exist
//---------------------------------------------------------------------------------
void DataManager::checkProjectDir()
{
    QString home = QDir().homePath();
    mProjectDir = home + "/Epigenetics_project";

    if( !QDir( mProjectDir ).exists() )
    {
        QDir().mkpath( mProjectDir );
    }
} // end of function DataManager::checkProjectDir()

//---------------------------------------------------------------------------------
//! Check Log dir and create if log dir not exist
//---------------------------------------------------------------------------------
void DataManager::checkDir
    (
    QString aDir
    )
{
    QString dirPath = mProjectDir + "/" + aDir;
    if( !QDir( dirPath ).exists() )
    {
        QDir().mkpath( dirPath );
    }

} // end of function DataManager::checkLogDir()

//---------------------------------------------------------------------------------
//! Save log file
//---------------------------------------------------------------------------------
void DataManager::saveLog
    (
    QString aLog
    )
{
    checkProjectDir();
    checkDir( "Log" );
    QDateTime dateTime = QDateTime().currentDateTime();
    QString dateTimeString = dateTime.toString( "yyyy_MM_dd_hh_mm_ss" );
    QString fileName = mLogDir + "/log_" + dateTimeString + ".txt";

    QFile file( fileName );
    file.open( QIODevice::WriteOnly );
    QDataStream out( &file );
    out << aLog;
    file.close();

    QString msg = "Log has been saved in " + fileName;
    processFinished( msg );
} // end of function DataManager::saveLog()

//---------------------------------------------------------------------------------
//! Move dir to dir which is under project dir
//---------------------------------------------------------------------------------
QString DataManager::moveDir
    (
    QString aDirPath,
    int aType
    )
{
    QString home = QDir().homePath();
    mProjectDir = home + "/Epigenetics_project";
    QStringList path = aDirPath.split( "/" );
    QString sDirPath = path[ path.length() - 1 ];
    QString preDir = path[ 0 ];

    for( int i = 1; i < path.length() - 1; i++ ){
        preDir += "/" + path[ i ];
    }

    if( aType == PROCESS_TYPE::TEPIC ){
        // Create dir for result file
        if( !QDir( aDirPath ).exists() )
        {
            QDir().mkpath( aDirPath );
        }
        copyFileWithPrefix( preDir, aDirPath, sDirPath );
    }
    checkDir( sDirPath );
    QString targetPath = mProjectDir + "/Result/" + sDirPath;
    copyRecursively( aDirPath, targetPath );
    return targetPath;

} // end of function DataManager::moveDir()

//---------------------------------------------------------------------------------
//! Copy file with prefix
//---------------------------------------------------------------------------------
bool DataManager::copyFileWithPrefix
    (
    const QString &aSrcFilePath,
    const QString &aTgtFilePath,
    const QString &aPrefix
    )
{

    QFileInfo srcFileInfo( aSrcFilePath );
    if( srcFileInfo.isDir() ){

        QDir sourceDir( aSrcFilePath );
        QStringList fileNames = sourceDir.entryList( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System );

        foreach( const QString &fileName, fileNames ){
            // Check prefix
            auto result = std::mismatch( aPrefix.begin(), aPrefix.end(), fileName.begin() );
            if( result.first == aPrefix.end() ){
                const QString newSrcFilePath = aSrcFilePath + QLatin1Char( '/' ) + fileName;
                const QString newTgtFilePath = aTgtFilePath + QLatin1Char( '/' ) + fileName;
                if ( !copyFileWithPrefix( newSrcFilePath, newTgtFilePath, aPrefix ) )
                    return false;
            }
        }
    }
    else{
        if( !QFile::copy(aSrcFilePath, aTgtFilePath ) )
            return false;
    }
    return true;
} // end of function DataManager::copyFileWithPrefix()

//---------------------------------------------------------------------------------
//! Copy dir recursively
//---------------------------------------------------------------------------------
bool DataManager::copyRecursively
    (
    const QString &aSrcFilePath,
    const QString &aTgtFilePath
    )
{
    QFileInfo srcFileInfo( aSrcFilePath );
    if( srcFileInfo.isDir() ){
        QDir targetDir( aTgtFilePath );
        targetDir.cdUp();
        if( !targetDir.mkdir( QFileInfo( aTgtFilePath ).fileName() ) )
            return false;
        QDir sourceDir( aSrcFilePath );
        QStringList fileNames = sourceDir.entryList( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System );
        foreach( const QString &fileName, fileNames ){
            const QString newSrcFilePath = aSrcFilePath + QLatin1Char( '/' ) + fileName;
            const QString newTgtFilePath = aTgtFilePath + QLatin1Char( '/' ) + fileName;
            if ( !copyRecursively( newSrcFilePath, newTgtFilePath ) )
                return false;
        }
    }
    else{
        if( !QFile::copy(aSrcFilePath, aTgtFilePath ) )
            return false;
    }
    return true;
} // end of function DataManager::copyRecursively()

//---------------------------------------------------------------------------------
//! Add dir or file path into filelist
//---------------------------------------------------------------------------------
void DataManager::addPath
    (
    QString aPath
    )
{
    mFileList.append( aPath );
} // end of function DataManager::addPath()

void DataManager::addFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString content = file.readAll();
    qInfo() << "Open File";
    cout << content.toStdString() << endl;
    file.close();
    //string tmp = fileName.toStdString();
    //fileNameList->push_back(tmp);
    //getFileNameList();
    return;
}

//---------------------------------------------------------------------------------
//! Return filelist
//---------------------------------------------------------------------------------
QStringList DataManager::getFileNameList()
{
    return mFileList;
} // end of function DataManager::addPath()


void DataManager::getFilePath()
{


}

