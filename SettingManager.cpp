/*********************************************************************
*
*   MODULE NAME:
*       SettingManager.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "SettingManager.hpp"
#include "DataManager.hpp"
#include <iostream>
#include <string>
#include <QMainWindow>

using namespace std;

SettingManager* SettingManager::sSettingManager = NULL;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
SettingManager::SettingManager() : QObject()
{
    mTepicPath = "";
    mPeakCallerPath = "";
    qInfo() << qgetenv("PATH");
} // end of function SettingManager::SettingManager()

//---------------------------------------------------------------------------------
//! Destructor
//---------------------------------------------------------------------------------
SettingManager::~SettingManager()
{

} // end of function SettingManager::~SettingManager()

//---------------------------------------------------------------------------------
//! Get analysis manager
//---------------------------------------------------------------------------------
SettingManager* SettingManager::getSettingManager()
{
    if( sSettingManager == NULL ){
        sSettingManager = new SettingManager();
    }
    return sSettingManager;
} // end of function SettingManager::getSettingManager()

//---------------------------------------------------------------------------------
//! Init
//---------------------------------------------------------------------------------
void SettingManager::init()
{
    if( !QFile( DataManager::getDataManager()->getProjectHomePath() + "/Setting.pro" ).exists() ){
        save();
    }
    load();
    if( mPeakCallerPath == "" ){
        getPeakCaller();
    }
    if( mTepicPath == "" ){
        getTepic();
    }
    save();

} // end of function SettingManager::init()

//---------------------------------------------------------------------------------
//! Get Peak caller JAMM
//---------------------------------------------------------------------------------
QString SettingManager::getPeakCaller()
{
    QString path = qgetenv( "PATH" );
    QStringList pathList = path.split(":");
    for( int i = 0; i < pathList.length(); i++ ){
        QString pathTmp = pathList.at( i );
        if( pathTmp.contains( "JAMM" ) ){
            mPeakCallerPath = pathTmp;
        }
    }
    return mPeakCallerPath;
} // end of function SettingManager::getPeakCaller()

//---------------------------------------------------------------------------------
//! Set Peak caller JAMM
//---------------------------------------------------------------------------------
void SettingManager::setPeakCaller
    (
    QString aPath
    )
{
    mPeakCallerPath = aPath;
} // end of function SettingManager::setPeakCaller()

//---------------------------------------------------------------------------------
//! Get TEPIC
//---------------------------------------------------------------------------------
QString SettingManager::getTepic()
{
    QString path = qgetenv( "PATH" );
    QStringList pathList = path.split(":");
    for( int i = 0; i < pathList.length(); i++ ){
        QString pathTmp = pathList.at( i );
        if( pathTmp.contains( "TEPIC" ) ){
            mTepicPath = pathTmp;
        }
    }
    return mTepicPath;
} // end of function SettingManager::getTepic()

//---------------------------------------------------------------------------------
//! Set TEPIC
//---------------------------------------------------------------------------------
void SettingManager::setTepic
    (
    QString aPath
    )
{
    mTepicPath = aPath;
} // end of function SettingManager::setTepic()

//---------------------------------------------------------------------------------
//! Save path
//---------------------------------------------------------------------------------
void SettingManager::save()
{
    QString settingFile = DataManager::getDataManager()->getProjectHomePath() + "/Setting.pro";
    QFile file( settingFile );
    file.open( QIODevice::WriteOnly );
    QTextStream streamFileOut( &file );
    streamFileOut.setCodec( "UTF-8" );
    streamFileOut << "Peak Call:\n";
    streamFileOut << mPeakCallerPath + "\n";
    streamFileOut << "TEPIC:\n";
    streamFileOut << mTepicPath + "\n";
    streamFileOut.flush();
    file.close();

} // end of function SettingManager::save()

//---------------------------------------------------------------------------------
//! Load path
//---------------------------------------------------------------------------------
void SettingManager::load()
{
    QString settingFile = DataManager::getDataManager()->getProjectHomePath() + "/Setting.pro";
    bool result = true;
    int peakCallIdx = 0;
    int tepicIdx = 0;
    int index = 0;
    QStringList textList;
    QFile file( settingFile );
    if( !file.open( QIODevice::ReadOnly ) ){
        result = false;
    }

    QTextStream text( &file );

    while( !text.atEnd() ){
        QString line = text.readLine();
        if( line == "Peak Call:" ){
            peakCallIdx = index;
        }
        else if( line == "TEPIC:" ){
            tepicIdx = index;
        }

        textList.append( line );
        index++;
    }

    mPeakCallerPath = textList.at( peakCallIdx + 1 );
    mTepicPath = textList.at( tepicIdx + 1 );

    file.close();
} // end of function SettingManager::load()
