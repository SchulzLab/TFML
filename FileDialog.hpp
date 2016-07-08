/*********************************************************************
*
*   HEADER NAME:
*       FileDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/
#ifndef FILEDIALOG_HPP
#define FILEDIALOG_HPP

#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include "FileListWidget.hpp"

class FileDialog: public QDialog
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
    FileDialog
        (
        int aSelectType,
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
    void handleClick
        (
        QStringList aFileName
        );

    void handleCancelClick();

    void handleClickOk();

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QTreeWidget *mTree;
    QLineEdit *mFileEdit;
    QLabel *mFileLabel;
    QLabel *mTypeLabel;
    QComboBox *mTypeComboBox;
    FileListWidget *mFileList;
    QString mFileName;
    QGroupBox *mInputWidget;
    int mType;
};
#endif // FILEDIALOG_HPP
