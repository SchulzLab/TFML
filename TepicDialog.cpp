/*********************************************************************
*
*   MODULE NAME:
*       TepicDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "AnalysisManager.hpp"
#include <iostream>
#include "TepicDialog.hpp"
#include "FileDialog.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
TepicDialog::TepicDialog
    (
    QWidget *parent
    )
    : QDialog( parent )
{
    mExtendInputWidgetBox = createExtendInputWidgets();
    mExtendInputWidgetBox->setVisible( false );
    mInputWidgetBox = createInputWidgets();

    mButtonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( mInputWidgetBox );
    layout->addWidget( mExtendInputWidgetBox );
    layout->addWidget( mButtonBox );
    layout->setSizeConstraint( QLayout::SetFixedSize);
    setLayout( layout );

    setWindowTitle( "TEPIC" );
} // end of function TepicDialog::TepicDialog()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *TepicDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox( "TEPIC" );

    mAnnotedRegLabel = new QLabel( "Regions to be annoted:" );
    mGenomeLabel = new QLabel( "Reference genome:" );
    mOutputLabel = new QLabel( "Prefix of output:" );
    mPwmLabel = new QLabel( "PWMs file:" );

    mAnnotedRegEditor = new QLineEdit;
    mGenomeEditor = new QLineEdit;
    mOutputEditor = new QLineEdit;
    mPwmEditor = new QLineEdit;

    mAnnotedRegButton = new QPushButton( "Select File" );
    mGenomeButton = new QPushButton( "Select File" );
    mPwmButton = new QPushButton( "Select File" );
    mMoreButton = new QPushButton( "Advanced setting" );

    mMoreButton->setCheckable( true );
    mAnnotedRegButton->setObjectName( "AnnotedRegButton" );
    mGenomeButton->setObjectName( "GenomeButton" );
    mPwmButton->setObjectName( "PwmButton" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mGenomeLabel, 0, 0 );
    layout->addWidget( mGenomeEditor, 0, 1 );
    layout->addWidget( mGenomeButton, 0, 2 );

    layout->addWidget( mAnnotedRegLabel, 1, 0 );
    layout->addWidget( mAnnotedRegEditor, 1, 1 );
    layout->addWidget( mAnnotedRegButton, 1, 2 );

    layout->addWidget( mOutputLabel, 2, 0 );
    layout->addWidget( mOutputEditor, 2, 1 );
    layout->addWidget( mMoreButton, 4, 2);

    layout->addWidget( mPwmLabel, 3, 0 );
    layout->addWidget( mPwmEditor, 3, 1 );
    layout->addWidget( mPwmButton, 3, 2 );
    connect( mAnnotedRegButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mGenomeButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mPwmButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mMoreButton, SIGNAL( toggled( bool ) ), mExtendInputWidgetBox, SLOT( setVisible( bool ) ) ) ;

    box->setLayout( layout );

    return box;
} // end of function TepicDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Create extended input widgets
//---------------------------------------------------------------------------------
QGroupBox *TepicDialog::createExtendInputWidgets()
{
    QGroupBox *extension = new QGroupBox();

    mGenomeAnnotedLabel = new QLabel( "Genome annoted file (gtf): (optional)" );
    mWindowSizeLabel = new QLabel( "Window size: (optional)" );
    mSignalOcLabel = new QLabel( "Signal of the open chromatin assay: (optional)" );
    mExpoDecayLabel = new QLabel( "Deactivates the exponential decay: (optional)" );
    mAvgSignalLabel = new QLabel( "Indicates average signal in the peaks: (optional)" );
    mNumCoreTrapLabel = new QLabel( "Number of cores used within TRAP: (optional)" );

    mGenomeAnnotedEditor = new QLineEdit;
    mWindowSizeEditor = new QLineEdit;
    mSignalOcEditor = new QLineEdit;
    mAvgSignalEditor = new QLineEdit;
    mNumCoreTrapEditor = new QLineEdit;
    mExpoDecayCheckBox = new QCheckBox;
    mGenomeAnnotedButton = new QPushButton( "Select file" );
    mSignalIOcButton  = new QPushButton( "Select File" );
    mSignalIOcButton->setObjectName( "SignalButton" );
    mGenomeAnnotedButton->setObjectName( "GenomeAnnotedButton" );

    QGridLayout *extendLayout = new QGridLayout;

    extendLayout->addWidget( mGenomeAnnotedLabel, 0, 0 );
    extendLayout->addWidget( mGenomeAnnotedEditor, 0, 1 );
    extendLayout->addWidget( mGenomeAnnotedButton, 0, 2 );


    extendLayout->addWidget( mWindowSizeLabel, 1, 0 );
    extendLayout->addWidget( mWindowSizeEditor, 1, 1 );

    extendLayout->addWidget( mSignalOcLabel, 2, 0 );
    extendLayout->addWidget( mSignalOcEditor, 2, 1 );
    extendLayout->addWidget( mSignalIOcButton, 2, 2 );

    extendLayout->addWidget( mExpoDecayLabel, 3, 0 );
    extendLayout->addWidget( mExpoDecayCheckBox, 3, 1 );

    extendLayout->addWidget( mAvgSignalLabel, 4, 0 );
    extendLayout->addWidget( mAvgSignalEditor, 4, 1 );

    extendLayout->addWidget( mNumCoreTrapLabel, 5, 0 );
    extendLayout->addWidget( mNumCoreTrapEditor, 5, 1 );

    connect( mGenomeAnnotedButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mSignalIOcButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    extension->setLayout( extendLayout );

    return extension;
} // end of function TepicDialog::createExtendInputWidgets()

//---------------------------------------------------------------------------------
//! Create buttons
//---------------------------------------------------------------------------------
QDialogButtonBox *TepicDialog::createButtons()
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
} // end of function TepicDialog::createButtons()

//---------------------------------------------------------------------------------
//! Handle click select file
//---------------------------------------------------------------------------------
void TepicDialog::selectFile()
{
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "AnnotedRegButton" ){
        edit = mAnnotedRegEditor;
    }
    else if( senderObjName == "GenomeButton" ){
        edit = mGenomeEditor;
    }
    else if( senderObjName == "PwmButton" ){
        edit = mPwmEditor;
    }
    else if( senderObjName == "SignalButton" ){
        edit = mPwmEditor;
    }

    FileDialog *dialog = new FileDialog( SELECT_TYPE::FILE );

    dialog->exec();
    if( !dialog->getFileName().isEmpty() ){
        edit->setText( dialog->getFileName() );
    }
} // end of function TepicDialog::selectFile()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void TepicDialog::handleClickOk()
{
    if( mAnnotedRegEditor->text().isEmpty() || mGenomeEditor->text().isEmpty() || mOutputEditor->text().isEmpty() || mPwmEditor->text().isEmpty() ){
        cout << "empty" << endl;
    }
    else {
        QString cmd = "-g " + mGenomeEditor->text() + " -b " + mAnnotedRegEditor->text() + " -o " + mOutputEditor->text() + " -p " + mPwmEditor->text();
        if( mExtendInputWidgetBox->isVisible() ){
            if( !mGenomeAnnotedEditor->text().isEmpty() ){
                cmd = cmd + " -c " + mGenomeAnnotedEditor->text();
            }
            if( !mWindowSizeEditor->text().isEmpty() ){
                cmd = cmd + " -w " + mWindowSizeEditor->text();
            }
            if( !mSignalOcLabel->text().isEmpty() ){
                cmd = cmd + " -d " + mSignalOcLabel->text();
            }
            if( !mExpoDecayCheckBox->isChecked() ){
                cmd = cmd + " -e ";
            }
            if( !mAvgSignalEditor->text().isEmpty() ){
                cmd = cmd + " -n " + mAvgSignalEditor->text();
            }
            if( !mNumCoreTrapEditor->text().isEmpty() ){
                cmd = cmd + " -c " + mNumCoreTrapEditor->text();
            }
        }

        accept();
        AnalysisManager::getAnalysisManager()->tepic( cmd, mOutputEditor->text() );
    }
} // end of function TepicDialog::ok()

