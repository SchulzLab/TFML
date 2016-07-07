/*********************************************************************
*
*   HEADER NAME:
*       TepicDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef TEPICDIALOG_HPP
#define TEPICDIALOG_HPP

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class TepicDialog: public QDialog
{
    Q_OBJECT

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    TepicDialog
        (
        QWidget *parent = 0
        );

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
private:
    QDialogButtonBox *createButtons();
    QGroupBox *createInputWidgets();
    QGroupBox *createExtendInputWidgets();

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
    QGroupBox *mExtendInputWidgetBox;
    QDialogButtonBox *mButtonBox;

    QComboBox *mResolutionBox;
    QComboBox *mPeakCallModeBox;
    QComboBox *mMixModelInitBox;
    QComboBox *mPcrDupBox;
    QComboBox *mAlignTypeBox;

    QLabel *mGenomeLabel;
    QLabel *mAnnotedRegLabel;
    QLabel *mOutputLabel;
    QLabel *mPwmLabel;
    QLabel *mGenomeAnnotedLabel;
    QLabel *mWindowSizeLabel;
    QLabel *mSignalOcLabel;
    QLabel *mExpoDecayLabel;
    QLabel *mAvgSignalLabel;
    QLabel *mNumCoreTrapLabel;

    QLineEdit *mGenomeEditor;
    QLineEdit *mAnnotedRegEditor;
    QLineEdit *mOutputEditor;
    QLineEdit *mPwmEditor;
    QLineEdit *mGenomeAnnotedEditor;
    QLineEdit *mWindowSizeEditor;
    QLineEdit *mSignalOcEditor;
    QLineEdit *mAvgSignalEditor;
    QLineEdit *mNumCoreTrapEditor;

    QCheckBox *mExpoDecayCheckBox;
    QPushButton *mAnnotedRegButton;
    QPushButton *mGenomeButton;
    QPushButton *mPwmButton;
    QPushButton *mGenomeAnnotedButton;
    QPushButton *mSignalIOcButton;
    QPushButton *mMoreButton;

};

#endif // TEPICDIALOG_HPP
