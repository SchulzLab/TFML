/*********************************************************************
*
*   HEADER NAME:
*       PeakCallingDialog.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef PEAKCALLINGDIALOG_H
#define PEAKCALLINGDIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class PeakCallingDialog : public QDialog
{
    Q_OBJECT

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    PeakCallingDialog
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
    void selectDirectory();
    void selectFile();
    void ok();

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

    QLabel *mSampleLabel;
    QLabel *mGenomeLabel;
    QLabel *mOutputLabel;
    QLabel *mControlLabel;
    QLabel *mFragLengthLabel;
    QLabel *mResolutionLabel;
    QLabel *mPeakCallModeLabel;
    QLabel *mMixModelInitLabel;
    QLabel *mBinSizeLabel;
    QLabel *mWindowFoldLabel;
    QLabel *mPcrDupLabel;
    QLabel *mAlignTypeLabel;
    QLabel *mMinWindowSizeLabel;
    QLabel *mNumProcLabel;

    QLineEdit *mSampleEditor;
    QLineEdit *mGenomeEditor;
    QLineEdit *mOutputEditor;
    QLineEdit *mControlEditor;
    QLineEdit *mFragLengthEditor;
    QLineEdit *mBinSizeEditor;
    QLineEdit *mWindowFoldEditor;
    QLineEdit *mMinWindowSizeEditor;
    QLineEdit *mNumProcEditor;

    QPushButton *mSampleButton;
    QPushButton *mGenomeButton;
    QPushButton *mControlButton;
    QPushButton *mMoreButton;

};
#endif // PEAKCALLINGDIALOG_H
