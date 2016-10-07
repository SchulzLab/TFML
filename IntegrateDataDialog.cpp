/*********************************************************************
*
*   MODULE NAME:
*       IntegrateDataDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "AnalysisManager.hpp"
#include "DataManager.hpp"
#include <iostream>
#include "IntegrateDataDialog.hpp"
#include "FileDialog.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
IntegrateDataDialog::IntegrateDataDialog
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
    layout->setSizeConstraint( QLayout::SetFixedSize );
    setLayout( layout );

    setWindowTitle( "Integrate data" );
} // end of function IntegrateDataDialog::IntegrateDataDialog()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *IntegrateDataDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox();

    mTfLabel = new QLabel( "TF affinity file:" );
    mExprLabel = new QLabel( "Expression file:" );
    mOutputLabel = new QLabel( "Prefix of output:" );

    mTfEditor = new QLineEdit;
    mExprEditor = new QLineEdit;
    mOutputEditor = new QLineEdit;

    mTfButton = new QPushButton( "Select File" );
    mExprButton = new QPushButton( "Select File" );

    mTfButton->setObjectName( "TF" );
    mExprButton->setObjectName( "Expression" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mTfLabel, 0, 0 );
    layout->addWidget( mTfEditor, 0, 1 );
    layout->addWidget( mTfButton, 0, 2 );

    layout->addWidget( mExprLabel, 1, 0 );
    layout->addWidget( mExprEditor, 1, 1 );
    layout->addWidget( mExprButton, 1, 2 );

    layout->addWidget( mOutputLabel, 2, 0 );
    layout->addWidget( mOutputEditor, 2, 1 );

    connect( mTfButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mExprButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );

    box->setLayout( layout );

    return box;
} // end of function IntegrateDataDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Create buttons
//---------------------------------------------------------------------------------
QDialogButtonBox *IntegrateDataDialog::createButtons()
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
} // end of function IntegrateDataDialog::createButtons()

//---------------------------------------------------------------------------------
//! Handle click select file
//---------------------------------------------------------------------------------
void IntegrateDataDialog::selectFile()
{
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "TF" ){
        edit = mTfEditor;
    }
    else if( senderObjName == "Expression" ){
        edit = mExprEditor;
    }

    FileDialog *dialog = new FileDialog( SELECT_TYPE::FILE );

    dialog->exec();
    if( !dialog->getFileName().isEmpty() ){
        edit->setText( dialog->getFileName() );
    }
} // end of function IntegrateDataDialog::selectFile()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void IntegrateDataDialog::handleClickOk()
{
    if( !mOutputEditor->text().isEmpty() && DataManager::getDataManager()->checkOutputDir( mOutputEditor->text() ) ){
        QMessageBox msgBox;
        msgBox.setWindowTitle( "Warning" );
        msgBox.setText( "Output directory is already existed. Please change to another output name." );
        msgBox.exec();
        return;
    }
    if( mTfEditor->text().isEmpty() || mExprEditor->text().isEmpty() || mOutputEditor->text().isEmpty() ){
        cout << "empty" << endl;
    }
    else {
        QString cmd = mTfEditor->text() + " " + mExprEditor->text();
        accept();
        AnalysisManager::getAnalysisManager()->integrateData( cmd, mOutputEditor->text() );
    }
} // end of function IntegrateDataDialog::ok()

