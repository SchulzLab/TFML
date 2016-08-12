/*********************************************************************
*
*   MODULE NAME:
*       DiffLearnDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DiffLearnDialog.hpp"
#include "AnalysisManager.hpp"
#include <iostream>
#include "FileDialog.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
DiffLearnDialog::DiffLearnDialog
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

    setWindowTitle( "Differentiate Learning" );
} // end of function DiffLearnDialog::DiffLearnDialog()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *DiffLearnDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox( "Peak Calling" );

    mNormalLabel = new QLabel( "Normal class directory:" );
    mDiseaseLabel = new QLabel( "Disease class directory:" );
    mOutputLabel = new QLabel( "Output Directory:" );

    mNormalEditor = new QLineEdit;
    mDiseaseEditor = new QLineEdit;
    mOutputEditor = new QLineEdit;

    mNormalButton = new QPushButton( "Select Directory" );
    mDiseaseButton = new QPushButton( "Select Directory" );
    mNormalButton->setObjectName( "NormalButton" );
    mDiseaseButton->setObjectName( "DiseaseButton" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mNormalLabel, 0, 0 );
    layout->addWidget( mNormalEditor, 0, 1 );
    layout->addWidget( mNormalButton, 0, 2 );

    layout->addWidget( mDiseaseLabel, 1, 0 );
    layout->addWidget( mDiseaseEditor, 1, 1 );
    layout->addWidget( mDiseaseButton, 1, 2 );

    layout->addWidget( mOutputLabel, 2, 0 );
    layout->addWidget( mOutputEditor, 2, 1 );

    connect( mNormalButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    connect( mDiseaseButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );

    box->setLayout( layout );

    return box;
} // end of function DiffLearnDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Create buttons
//---------------------------------------------------------------------------------
QDialogButtonBox *DiffLearnDialog::createButtons()
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
} // end of function DiffLearnDialog::createButtons()

//---------------------------------------------------------------------------------
//! Handle click directory
//---------------------------------------------------------------------------------
void DiffLearnDialog::selectDirectory()
{
    QObject *senderObj = sender(); // This will give Sender object
    // This will give obejct name for above it will give "A", "B", "C"
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "NormalButton" ){
        edit = mNormalEditor;
    }
    else if( senderObjName == "DiseaseButton" ){
        edit = mDiseaseEditor;
    }

    FileDialog *dialog = new FileDialog( SELECT_TYPE::DIR );

    dialog->exec();
    if( !dialog->getFileName().isEmpty() ){
        edit->setText( dialog->getFileName() );
    }

} // end of function DiffLearnDialog::selectDirectory()

//---------------------------------------------------------------------------------
//! Handle click select file
//---------------------------------------------------------------------------------
void DiffLearnDialog::selectFile()
{
    FileDialog *dialog = new FileDialog( SELECT_TYPE::FILE );

    dialog->exec();
    if( !dialog->getFileName().isEmpty() ){
        mDiseaseEditor->setText( dialog->getFileName() );
    }

} // end of function DiffLearnDialog::selectFile()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void DiffLearnDialog::handleClickOk()
{
    if( mNormalEditor->text().isEmpty() || mDiseaseEditor->text().isEmpty() || mOutputEditor->text().isEmpty()) {
        cout << "empty" << endl;
    }
    else {
        QString cmd = mNormalEditor->text() + " " + mDiseaseEditor->text() + " " + mOutputEditor->text();
        accept();
        AnalysisManager::getAnalysisManager()->diffLearning( cmd, mOutputEditor->text() );
    }
} // end of function DiffLearnDialog::ok()
