/*********************************************************************
*
*   MODULE NAME:
*       DataManager.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "ui_MainWindow.h"
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
    mProjectDir = "";
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
void DataManager::checkProjectHomeDir()
{
    if( !QDir( getProjectHomePath() ).exists() )
    {
        QDir().mkpath( getProjectHomePath() );
    }
} // end of function DataManager::checkProjectHomeDir()

//---------------------------------------------------------------------------------
//! Check dir and create if log dir not exist
//---------------------------------------------------------------------------------
bool DataManager::checkDir
    (
    QString aDir
    )
{
    bool result = true;
    QString dirPath = getProjectPath() + "/" + aDir;
    if( !QDir( dirPath ).exists() )
    {
        QDir().mkpath( dirPath );
    }
    else
    {
        result = false;
    }
    return result;

} // end of function DataManager::checkDir()

//---------------------------------------------------------------------------------
//! Check output dir
//---------------------------------------------------------------------------------
bool DataManager::checkOutputDir
    (
    QString aDir
    )
{
    bool result = false;
    QString dirPath = getProjectPath() + "/Result/" + aDir;
    if( QDir( dirPath ).exists() )
    {
        result = true;
    }
    return result;

} // end of function DataManager::checkOutputDir()

//---------------------------------------------------------------------------------
//! Save log file
//---------------------------------------------------------------------------------
void DataManager::saveLog
    (
    QString aLog
    )
{
    checkProjectHomeDir();
    checkDir( "Log" );
    mLogDir = getProjectPath() + "/Log";
    QDateTime dateTime = QDateTime().currentDateTime();
    QString dateTimeString = dateTime.toString( "yyyy_MM_dd_hh_mm_ss" );
    QString fileName = mLogDir + "/log_" + dateTimeString + ".txt";

    QFile file( fileName );
    file.open( QIODevice::WriteOnly );
    QTextStream streamFileOut( &file );
    streamFileOut.setCodec( "UTF-8" );
    streamFileOut << aLog;
    streamFileOut.flush();
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
    QString projectPath = getProjectPath();
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
        copyFileWithPrefix( preDir , aDirPath, sDirPath + "_" );
    }
    checkDir( "Result" );
    QString targetPath = projectPath + "/Result/" + sDirPath;
    // Copy corresponding result dir to result dir under project folder
    copyRecursively( aDirPath, targetPath );
    QDir dir( aDirPath );
    dir.removeRecursively();
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
        if( !QFile::copy( aSrcFilePath, aTgtFilePath ) )
            return false;
        else{
            QFile::remove( aSrcFilePath );
        }
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
        if( !targetDir.mkpath( QFileInfo( aTgtFilePath ).fileName() ) )
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
        if( !QFile::copy( aSrcFilePath, aTgtFilePath ) )
            return false;
        else{
            QFile::remove( aSrcFilePath );
        }
    }
    return true;
} // end of function DataManager::copyRecursively()

//---------------------------------------------------------------------------------
//! Check if path already in list
//---------------------------------------------------------------------------------
bool DataManager::checkPath
    (
    QString aPath
    )
{
    bool result = true;
    if( mResultFileList.indexOf(aPath) == -1 ){
        result = false;
    }
    return result;
} // end of function DataManager::checkPath()

//---------------------------------------------------------------------------------
//! Add dir or file path into filelist
//---------------------------------------------------------------------------------
void DataManager::addPath
    (
    QString aPath
    )
{
    if( mFileList.indexOf(aPath) == -1 ){
        mFileList.append( aPath );
        saveProjectFile();
    }
} // end of function DataManager::addPath()

//---------------------------------------------------------------------------------
//! Delete dir or file path from filelist
//---------------------------------------------------------------------------------
void DataManager::delPath
    (
    QString aPath
    )
{
    int len = mFileList.length();
    for( int i = 0; i < len; i++ ){
        if( mFileList.at( i ) == aPath ){
            qInfo() << i << mFileList[i];
            mFileList.removeAt( i );
            break;
        }
    }
    saveProjectFile();
} // end of function DataManager::delPath()

//---------------------------------------------------------------------------------
//! Add dir or file path into resultlist
//---------------------------------------------------------------------------------
void DataManager::addResultPath
    (
    QString aPath
    )
{
    if( mResultFileList.indexOf(aPath) == -1 ){
        mResultFileList.append( aPath );
        saveProjectFile();
    }
} // end of function DataManager::addResultPath()

//---------------------------------------------------------------------------------
//! Delete dir or file path from resultlist
//---------------------------------------------------------------------------------
void DataManager::delResultPath
    (
    QString aPath
    )
{
    int len = mResultFileList.length();
    for( int i = 0; i < len; i++ ){
        if( mResultFileList.at( i ) == aPath ){
            mResultFileList.removeAt( i );
            break;
        }
    }
    saveProjectFile();
} // end of function DataManager::delPath()

void DataManager::addFile( QString fileName )
{
    QFile file( fileName );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
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
} // end of function DataManager::getFileNameList()

//---------------------------------------------------------------------------------
//! Return result filelist
//---------------------------------------------------------------------------------
QStringList DataManager::getResultFileNameList()
{
    return mResultFileList;
} // end of function DataManager::getResultFileNameList()

void DataManager::getFilePath()
{


}

//---------------------------------------------------------------------------------
//! Get project home dir
//---------------------------------------------------------------------------------
QString DataManager::getProjectHomePath()
{
    QString home = QDir().homePath();
    QString homePath = home + '/' + cProjectHomeDir;

    return homePath;
} // end of function DataManager::getProjectHomePath()

//---------------------------------------------------------------------------------
//! Get project dir
//---------------------------------------------------------------------------------
QString DataManager::getProjectPath()
{
    QString home = getProjectHomePath();
    QString projectPath = home + '/' + mProjectDir;

    return projectPath;
} // end of function DataManager::getProjectPath()

//---------------------------------------------------------------------------------
//! Get project file path
//---------------------------------------------------------------------------------
QString DataManager::getProjectFilePath()
{
    QString filePath = getProjectPath() + "/" + getProjectName() + ".pro";

    return filePath;
} // end of function DataManager::getProjectFilePath()

//---------------------------------------------------------------------------------
//! Get project dir
//---------------------------------------------------------------------------------
QString DataManager::getProjectName()
{
    return mProjectDir;
} // end of function DataManager::getProjectName()

//---------------------------------------------------------------------------------
//! Create project dir
//---------------------------------------------------------------------------------
bool DataManager::createProjectDir
    (
    QString aDir
    )
{
    bool result = true;
    result = checkDir( aDir );
    checkProjectHomeDir();
    checkDir( "Log" );
    QString fileName = getProjectFilePath();

    QFile file( fileName );
    file.open( QIODevice::WriteOnly );
    file.close();
    QStringList nameList = aDir.split( "/" );
    mProjectDir = nameList.at( nameList.length() - 1 );
    return result;
} // end of function DataManager::createProjectDir()

//---------------------------------------------------------------------------------
//! Set active project
//---------------------------------------------------------------------------------
void DataManager::setActiveProject
    (
    QString aDir
    )
{
    mProjectDir = aDir;
    hasActiveProject( true );
} // end of function DataManager::setActiveProject()

//---------------------------------------------------------------------------------
//! Load project
//---------------------------------------------------------------------------------
bool DataManager::loadProject
    (
    QString aFilePath
    )
{
    bool result = true;
    int projectIdx = 0;
    int fileIdx = 0;
    int resultIdx = 0;
    int index = 0;
    QStringList textList;
    QFile file( aFilePath );
    if( !file.open( QIODevice::ReadOnly ) ){
        result = false;
    }

    QTextStream text( &file );

    while( !text.atEnd() ){
        QString line = text.readLine();
        if( line == "Project name:" ){
            projectIdx = index;
        }
        else if( line == "File directory:" ){
            fileIdx = index;
        }
        else if( line == "Result directory:"){
            resultIdx = index;
        }
        textList.append( line );
        index++;
    }
    mFileList.clear();
    for( int i = fileIdx + 1; i < resultIdx; i++ ){
        mFileList.append( textList.at( i ) );
        qInfo() << textList.at( i );
    }

    mResultFileList.clear();
    for( int i = resultIdx + 1; i < index; i++ ){
        mResultFileList.append( textList.at( i ) );
        qInfo() << textList.at( i );
    }

    file.close();
    return result;
} // end of function DataManager::setActiveProject()

//---------------------------------------------------------------------------------
//! Save project file
//---------------------------------------------------------------------------------
void DataManager::saveProjectFile()
{
    QString projectFile = getProjectFilePath();
    QFile file( projectFile );
    file.open( QIODevice::WriteOnly );
    QTextStream streamFileOut( &file );
    streamFileOut.setCodec( "UTF-8" );
    streamFileOut << "Project name:\n";
    streamFileOut << mProjectDir + "\n";
    streamFileOut << "File directory:\n";
    for( int i = 0; i < mFileList.length(); i++ ){
        streamFileOut << mFileList.at( i ) + "\n";
    }
    streamFileOut << "Result directory:\n";
    for( int i = 0; i < mResultFileList.length(); i++ ){
        streamFileOut << mResultFileList.at( i ) + "\n";
    }
    streamFileOut.flush();
    file.close();
} // end of function DataManager::saveProjectFile()
