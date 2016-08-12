/*********************************************************************
*
*   HEADER NAME:
*       DiffLearnDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef DIFFLEARNDIALOG_H
#define DIFFLEARNDIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class DiffLearnDialog : public QDialog
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
    DiffLearnDialog
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

    void selectFile();

    void handleClickOk();

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QGroupBox *mInputWidgetBox;
    QDialogButtonBox *mButtonBox;

    QLabel *mNormalLabel;
    QLabel *mDiseaseLabel;
    QLabel *mOutputLabel;

    QLineEdit *mNormalEditor;
    QLineEdit *mDiseaseEditor;
    QLineEdit *mOutputEditor;

    QPushButton *mNormalButton;
    QPushButton *mDiseaseButton;
    QPushButton *mControlButton;
};
#endif // DIFFLEARNDIALOG_H
