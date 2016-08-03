/*********************************************************************
*
*   HEADER NAME:
*       IntegrateDataDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef INTEGRATEDATADIALOG_HPP
#define INTEGRATEDATADIALOG_HPP

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class IntegrateDataDialog: public QDialog
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
    IntegrateDataDialog
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
    void selectFile();

    void handleClickOk();

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------
private:
    QGroupBox *mInputWidgetBox;
    QDialogButtonBox *mButtonBox;

    QLabel *mTfLabel;
    QLabel *mExprLabel;
    QLabel *mOutputLabel;

    QLineEdit *mTfEditor;
    QLineEdit *mExprEditor;
    QLineEdit *mOutputEditor;

    QPushButton *mTfButton;
    QPushButton *mExprButton;

};

#endif // INTEGRATEDATADIALOG_HPP
