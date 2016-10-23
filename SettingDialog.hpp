/*********************************************************************
*
*   HEADER NAME:
*       SettingDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class SettingDialog : public QDialog
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
    SettingDialog
        (
        QWidget *parent = 0
        );

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
private:
    QDialogButtonBox *createButtons();
    QGroupBox *createInputWidgets();

//----------------------------------------------------------------
// Slots
//----------------------------------------------------------------
private slots:
    void selectDirectory();

    void handleClickOk();

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QGroupBox *mInputWidgetBox;
    QDialogButtonBox *mButtonBox;

    QLabel *mPeakCallLabel;
    QLabel *mTepicLabel;

    QLineEdit *mPeakCallEditor;
    QLineEdit *mTepicEditor;

    QPushButton *mPeakCallButton;
    QPushButton *mTepicButton;
};
#endif // SETTINGDIALOG_H
