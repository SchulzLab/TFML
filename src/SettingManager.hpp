/*********************************************************************
*
*   HEADER NAME:
*       SettingManager.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class SettingManager : public QObject
{
    Q_OBJECT

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    static SettingManager* getSettingManager();

    ~SettingManager();

    void init();

    QString getPeakCaller();

    QString getTepic();

    QString getScript();

    void setPeakCaller
        (
        QString aPath
        );

    void setTepic
        (
        QString aPath
        );

    void setScript
        (
        QString aPath
        );

    void save();

private:
    SettingManager();

    void load();

//----------------------------------------------------------------
// Signals
//----------------------------------------------------------------


//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:

    static SettingManager* sSettingManager;

    QString mPeakCallerPath;

    QString mTepicPath;

    QString mScriptPath;
};

#endif // SETTINGMANAGER_H
