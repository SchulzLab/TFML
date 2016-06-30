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

DataManager* DataManager::dataManager = NULL;

DataManager::DataManager()
{
    cout << "DataManager()" << endl;
    fileNameList = new vector<string>();
    //connect(AnalysisManager::getAnalysisManager(), SIGNAL(peakCallingDone(QString)), this, SLOT(addDirectoryPath(QString)));
}

DataManager* DataManager::getDataManager()
{
    if( dataManager == NULL ){
        cout << "dataManager == NULL" << endl;
        dataManager = new DataManager();
    }
    return dataManager;
}

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

void DataManager::getFileNameList()
{
    for(int i=0; i < fileNameList->size(); i++){
        cout << fileNameList->at(i) << endl;
    }

}

void DataManager::updateDataList()
{


}

void DataManager::getFilePath()
{


}

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
void DataManager::checkLogDir()
{
    mLogDir = mProjectDir + "/Log";
    if( !QDir( mLogDir ).exists() )
    {
        QDir().mkpath( mLogDir );
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
    checkLogDir();
    QDateTime dateTime = QDateTime().currentDateTime();
    QString dateTimeString = dateTime.toString( "yyyy-MM-dd-hh-mm-ss" );
    QString fileName = mLogDir + "/Log-" + dateTimeString + ".txt";
    QFile file( fileName );
    file.open( QIODevice::WriteOnly );
    QDataStream out( &file );
    out << aLog;
    file.close();
} // end of function DataManager::saveLog()

void DataManager::addDirectoryPath(QString directoryPath)
{
    QDir *d = new QDir(directoryPath);
    d->setFilter( QDir::Hidden | QDir::NoSymLinks );
    d->setSorting( QDir::Size | QDir::Reversed );
    qInfo() << directoryPath;
    const QFileInfoList list = d->entryInfoList();
    QFileInfoList::const_iterator iterator = list.begin();

    cout << "Filename\t\tSize" << endl;
    while ( iterator != list.end() ) {
        cout << qPrintable((*iterator).fileName()) << "\t"
             << (*iterator).size() << endl;
        ++iterator;
    }

}
