/*********************************************************************
*
*   HEADER NAME:
*       ProjectDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/
#ifndef PROJECTDIALOG_HPP
#define PROJECTDIALOG_HPP

#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include "FileListWidget.hpp"

class ProjectDialog: public QDialog
{
    Q_OBJECT

public:
    enum SELECT_TYPE
    {
        FILE = 0,
        DIR = 1
    };

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    ProjectDialog
        (
        QWidget *parent = 0
        );

    QString getFileName();

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
private:
    QGroupBox *createInputWidgets();
    void init();
//----------------------------------------------------------------
// Slots
//----------------------------------------------------------------
private slots:
    void handleCancelClick();

    void handleClickOk();

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QTreeWidget *mTree;
    QLineEdit *mFileEdit;
    QLabel *mFileLabel;
    QLabel *mDirNameLabel;
    QLabel *mDirLabel;
    QGroupBox *mInputWidget;
    int mType;
};
#endif // PROJECTDIALOG_HPP
