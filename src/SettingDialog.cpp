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
    mScriptLabel = new QLabel( "Script path:" );

    mPeakCallEditor = new QLineEdit;
    mTepicEditor = new QLineEdit;
    mScriptEditor = new QLineEdit;
    mPeakCallEditor->setText( SettingManager::getSettingManager()->getPeakCaller() );
    mTepicEditor->setText( SettingManager::getSettingManager()->getTepic() );
    mScriptEditor->setText( SettingManager::getSettingManager()->getScript() );

    mPeakCallButton = new QPushButton( "Select Directory" );
    mTepicButton = new QPushButton( "Select Directory" );
    mScriptButton = new QPushButton( "Select Directory" );

    mPeakCallButton->setObjectName( "PeakCallButton" );
    mTepicButton->setObjectName( "TepicButton" );
    mScriptButton->setObjectName( "ScriptButton" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mPeakCallLabel, 0, 0 );
    layout->addWidget( mPeakCallEditor, 0, 1 );
    layout->addWidget( mPeakCallButton, 0, 2 );

    layout->addWidget( mTepicLabel, 1, 0 );
    layout->addWidget( mTepicEditor, 1, 1 );
    layout->addWidget( mTepicButton, 1, 2 );

    layout->addWidget( mScriptLabel, 2, 0 );
    layout->addWidget( mScriptEditor, 2, 1 );
    layout->addWidget( mScriptButton, 2, 2 );

    connect( mPeakCallButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    connect( mTepicButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    connect( mScriptButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );

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
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "PeakCallButton" ){
        edit = mPeakCallEditor;
    }
    else if( senderObjName == "TepicButton" ){
        edit = mTepicEditor;
    }
    else if( senderObjName == "ScriptButton" ){
        edit = mScriptEditor;
    }
    QString path = QFileDialog::getExistingDirectory( this, tr( "select path" ), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

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
    SettingManager::getSettingManager()->setTepic( mTepicEditor->text() );
    SettingManager::getSettingManager()->setScript( mScriptEditor->text() );
    SettingManager::getSettingManager()->save();
    accept();
} // end of function SettingDialog::ok()
