/*********************************************************************
*
*   MODULE NAME:
*       SettingDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "SettingDialog.hpp"
#include "SettingManager.hpp"
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
SettingDialog::SettingDialog
    (
    QWidget *parent
    )
    : QDialog( parent )
{
    mInputWidgetBox = createInputWidgets();

    mButtonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( mInputWidgetBox );
    layout->addWidget( mButtonBox );
    layout->setSizeConstraint( QLayout::SetFixedSize);
    setLayout( layout );

    setWindowTitle( "Settings" );
} // end of function SettingDialog::SettingDialog()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *SettingDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox( "Settings" );

    mPeakCallLabel = new QLabel( "Peak Caller path:" );
    mTepicLabel = new QLabel( "TEPIC path:" );

    mPeakCallEditor = new QLineEdit;
    mTepicEditor = new QLineEdit;
    mPeakCallEditor->setText( SettingManager::getSettingManager()->getPeakCaller() );
    mTepicEditor->setText( SettingManager::getSettingManager()->getTepic() );

    mPeakCallButton = new QPushButton( "Select Directory" );
    mTepicButton = new QPushButton( "Select Directory" );

    mPeakCallButton->setObjectName( "PeakCallButton" );
    mTepicButton->setObjectName( "TepicButton" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mPeakCallLabel, 0, 0 );
    layout->addWidget( mPeakCallEditor, 0, 1 );
    layout->addWidget( mPeakCallButton, 0, 2 );

    layout->addWidget( mTepicLabel, 1, 0 );
    layout->addWidget( mTepicEditor, 1, 1 );
    layout->addWidget( mTepicButton, 1, 2 );

    connect( mPeakCallButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    connect( mTepicButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );

    box->setLayout( layout );

    return box;
} // end of function SettingDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Create buttons
//---------------------------------------------------------------------------------
QDialogButtonBox *SettingDialog::createButtons()
{
    QPushButton *cancelButton = new QPushButton( tr( "&Cancel" ) );
    QPushButton *okButton = new QPushButton( tr( "&OK" ) );

    cancelButton->setDefault( true );

    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( handleClickOk() ) );
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton( okButton, QDialogButtonBox::ResetRole );
    buttonBox->addButton( cancelButton, QDialogButtonBox::RejectRole );

    return buttonBox;
} // end of function SettingDialog::createButtons()

//---------------------------------------------------------------------------------
//! Handle click directory
//---------------------------------------------------------------------------------
void SettingDialog::selectDirectory()
{
    QObject *senderObj = sender(); // This will give Sender object
    // This will give obejct name for above it will give "A", "B", "C"
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "PeakCallButton" ){
        edit = mPeakCallEditor;
    }
    else if( senderObjName == "TepicButton" ){
        edit = mTepicEditor;
    }
    QFileDialog *dialog = new QFileDialog();
    QString path = dialog->getOpenFileName( this, tr( "select path" ) );

    if( !path.isEmpty() ){
        edit->setText( path );
    }

} // end of function SettingDialog::selectDirectory()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void SettingDialog::handleClickOk()
{
    SettingManager::getSettingManager()->setPeakCaller( mPeakCallEditor->text() );
    SettingManager::getSettingManager()->setPeakCaller( mTepicEditor->text() );
    SettingManager::getSettingManager()->save();
} // end of function SettingDialog::ok()
