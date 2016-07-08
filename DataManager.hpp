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
#include <vector>

using namespace std;

class DataManager : public QObject
{
    Q_OBJECT

public:
    enum PROCESS_TYPE
    {
        PEAK_CALLING = 0,
        TEPIC = 1
    };

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    static DataManager* getDataManager();

    void addFile(QString fileName);

    ~DataManager();

    void addPath
        (
        QString aPath
        );

    void saveLog
        (
        QString aLog
        );

    QString moveDir
        (
        QString aDirPath,
        int aType
        );

    QStringList getFileNameList();

private:
    DataManager();

    void getFilePath();

    void checkProjectDir();

    void checkDir
        (
        QString aDir
        );

    void updateDataList();

    bool copyRecursively
        (
        const QString &aSrcFilePath,
        const QString &aTgtFilePath
        );

    bool copyFileWithPrefix
        (
        const QString &aSrcFilePath,
        const QString &aTgtFilePath,
        const QString &aPrefix
        );
//----------------------------------------------------------------
// Signals
//----------------------------------------------------------------
signals:
    void processFinished
        (
        QString aMsg
        );

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    static DataManager* sDataManager;
    vector<string> *fileNameList;
    vector<int> fileIndex;
    QString mProjectDir;
    QString mLogDir;
    QStringList mFileList;
};

#endif // DATAMANAGER_H
