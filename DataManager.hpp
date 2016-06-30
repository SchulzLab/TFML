/*********************************************************************
*
*   HEADER NAME:
*       DataManager.h
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QMainWindow>

using namespace std;

class DataManager
{

public:
    static DataManager* getDataManager();
    void addFile(QString fileName);
    ~DataManager();
    void addDirectoryPath(QString directoryPath);
    void saveLog
        (
        QString aLog
        );
private:
    DataManager();
    void getFileNameList();
    void getFilePath();
    void checkProjectDir();
    void checkLogDir();
    void updateDataList();
    static DataManager* dataManager;
    vector<string> *fileNameList;
    vector<int> fileIndex;
    QString mProjectDir;
    QString mLogDir;
};

#endif // DATAMANAGER_H
