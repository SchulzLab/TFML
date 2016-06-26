/*********************************************************************
*
*   MODULE NAME:
*       peakcallingdialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "peakcallingdialog.h"
#include "analysismanager.h"
#include <iostream>

using namespace std;

PeakCallingDialog::PeakCallingDialog
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

    setWindowTitle( "Peak Calling" );
}

QGroupBox *PeakCallingDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox( "Peak Calling" );

    mSampleLabel = new QLabel( "Sample Directory:" );
    mGenomeLabel = new QLabel( "Genome File:" );
    mOutputLabel = new QLabel( "Output Directory:" );

    mSampleEditor = new QLineEdit;
    mGenomeEditor = new QLineEdit;
    mOutputEditor = new QLineEdit;

    mSampleButton = new QPushButton( "Select Directory" );
    mGenomeButton = new QPushButton( "Select File" );
    mMoreButton = new QPushButton( "Advanced setting" );
    mMoreButton->setCheckable( true );
    mSampleButton->setObjectName( "SampleButton" );
    mGenomeButton->setObjectName( "GenomeButton" );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mSampleLabel, 0, 0 );
    layout->addWidget( mSampleEditor, 0, 1 );
    layout->addWidget( mSampleButton, 0, 2 );

    layout->addWidget( mGenomeLabel, 1, 0 );
    layout->addWidget( mGenomeEditor, 1, 1 );
    layout->addWidget( mGenomeButton, 1, 2 );

    layout->addWidget( mOutputLabel, 2, 0 );
    layout->addWidget( mOutputEditor, 2, 1 );
    layout->addWidget( mMoreButton, 3, 2);
    connect( mSampleButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    connect( mGenomeButton, SIGNAL( clicked() ), this, SLOT( selectFile() ) );
    connect( mMoreButton, SIGNAL( toggled( bool ) ), mExtendInputWidgetBox, SLOT( setVisible( bool ) ) ) ;

    box->setLayout( layout );

    return box;
}

QGroupBox *PeakCallingDialog::createExtendInputWidgets()
{
    QGroupBox *extension = new QGroupBox();

    mControlLabel = new QLabel( "Control files directory: (optional)" );
    mFragLengthLabel = new QLabel( "Fragment Length: (optional)" );
    mResolutionLabel = new QLabel( "Peak calling resolution: (optional)" );
    mPeakCallModeLabel = new QLabel( "Peak calling mode: (optional)" );
    mMixModelInitLabel = new QLabel( "Mixture model initialization: (optional)" );
    mBinSizeLabel = new QLabel( "Bin size: (optional)" );
    mWindowFoldLabel = new QLabel( "Window fold enrichment: (optional)" );
    mPcrDupLabel = new QLabel( "Keep PCR duplicates: (optional)" );
    mAlignTypeLabel = new QLabel( "Alignment type: (optional)" );
    mMinWindowSizeLabel = new QLabel( "Minimum window size: (optional)" );
    mNumProcLabel = new QLabel( "Number of processors used: (optional)" );

    mControlEditor = new QLineEdit;
    mFragLengthEditor = new QLineEdit;
    mBinSizeEditor = new QLineEdit;
    mWindowFoldEditor = new QLineEdit;
    mMinWindowSizeEditor = new QLineEdit;
    mNumProcEditor = new QLineEdit;

    mControlButton = new QPushButton( "Select Directory" );

    mResolutionBox = new QComboBox();
    mPeakCallModeBox = new QComboBox();
    mMixModelInitBox = new QComboBox();
    mPcrDupBox = new QComboBox();
    mAlignTypeBox = new QComboBox();

    mResolutionBox->addItem( "peak" );
    mResolutionBox->addItem( "region" );
    mResolutionBox->addItem( "window" );

    mPeakCallModeBox->addItem( "normal" );
    mPeakCallModeBox->addItem( "narrow" );

    mMixModelInitBox->addItem( "deterministic" );
    mMixModelInitBox->addItem( "stochastic" );

    mPcrDupBox->addItem( "n" );
    mPcrDupBox->addItem( "y" );

    mAlignTypeBox->addItem( "single" );
    mAlignTypeBox->addItem( "paired" );

    mControlButton->setObjectName( "ControlButton" );

    QGridLayout *extendLayout = new QGridLayout;

    extendLayout->addWidget( mControlLabel, 0, 0 );
    extendLayout->addWidget( mControlEditor, 0, 1 );
    extendLayout->addWidget( mControlButton, 0, 2 );


    extendLayout->addWidget( mFragLengthLabel, 1, 0 );
    extendLayout->addWidget( mFragLengthEditor, 1, 1 );

    extendLayout->addWidget( mResolutionLabel, 2, 0 );
    extendLayout->addWidget( mResolutionBox, 2, 1 );

    extendLayout->addWidget( mPeakCallModeLabel, 3, 0 );
    extendLayout->addWidget( mPeakCallModeBox, 3, 1 );

    extendLayout->addWidget( mMixModelInitLabel, 4, 0 );
    extendLayout->addWidget( mMixModelInitBox, 4, 1 );

    extendLayout->addWidget( mBinSizeLabel, 5, 0 );
    extendLayout->addWidget( mBinSizeEditor, 5, 1 );

    extendLayout->addWidget( mWindowFoldLabel, 6, 0 );
    extendLayout->addWidget( mWindowFoldEditor, 6, 1 );

    extendLayout->addWidget( mPcrDupLabel, 7, 0 );
    extendLayout->addWidget( mPcrDupBox, 7, 1 );

    extendLayout->addWidget( mAlignTypeLabel, 8, 0 );
    extendLayout->addWidget( mAlignTypeBox, 8, 1 );

    extendLayout->addWidget( mMinWindowSizeLabel, 9, 0 );
    extendLayout->addWidget( mMinWindowSizeEditor, 9, 1 );

    extendLayout->addWidget( mNumProcLabel, 10, 0 );
    extendLayout->addWidget( mNumProcEditor, 10, 1 );

    connect( mControlButton, SIGNAL( clicked() ), this, SLOT( selectDirectory() ) );
    extension->setLayout( extendLayout );

    return extension;
}

QDialogButtonBox *PeakCallingDialog::createButtons()
{
    QPushButton *cancelButton = new QPushButton( tr( "&Cancel" ) );
    QPushButton *okButton = new QPushButton( tr( "&OK" ) );

    cancelButton->setDefault( true );

    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton( okButton, QDialogButtonBox::ResetRole );
    buttonBox->addButton( cancelButton, QDialogButtonBox::RejectRole );

    return buttonBox;
}

void PeakCallingDialog::selectDirectory()
{
    QObject *senderObj = sender(); // This will give Sender object
    // This will give obejct name for above it will give "A", "B", "C"
    QString senderObjName = senderObj->objectName();

    QLineEdit *edit;
    if( senderObjName == "SampleButton" ){
        edit = mSampleEditor;
    }
    else if( senderObjName == "ControlButton" ){
        edit = mControlEditor;
    }

    QFileDialog *dialog = new QFileDialog();
    QString directoryName = dialog->getExistingDirectory(this,tr("select file"), "/home", QFileDialog::ShowDirsOnly
                                               | QFileDialog::DontResolveSymlinks);
    edit->setText( directoryName );
}

void PeakCallingDialog::selectFile()
{
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, "select file" );
    mGenomeEditor->setText( fileName );
}

void PeakCallingDialog::ok()
{
    if( mSampleEditor->text().isEmpty() || mGenomeEditor->text().isEmpty() || mOutputEditor->text().isEmpty()) {
        cout << "empty" << endl;
    }
    else {
        QString cmd = "-s " + mSampleEditor->text() + " -g " + mGenomeEditor->text() + " -o " + mOutputEditor->text();
        if( mExtendInputWidgetBox->isVisible() ){
            qInfo() << "is visible";
            if( !mControlEditor->text().isEmpty() ){
                cmd = cmd + " -c " + mControlEditor->text();
            }
            if( !mFragLengthEditor->text().isEmpty() ){
                cmd = cmd + " -f " + mFragLengthEditor->text();
            }
            if( !mResolutionBox->currentText().isEmpty() ){
                cmd = cmd + " -r " + mResolutionBox->currentText();
            }
            if( !mPeakCallModeBox->currentText().isEmpty() ){
                cmd = cmd + " -m " + mPeakCallModeBox->currentText();
            }
            if( !mMixModelInitBox->currentText().isEmpty() ){
                cmd = cmd + " -i " + mMixModelInitBox->currentText();
            }
            if( !mBinSizeEditor->text().isEmpty() ){
                cmd = cmd + " -b " + mBinSizeEditor->text();
            }
            if( !mWindowFoldEditor->text().isEmpty() ){
                cmd = cmd + " -e " + mWindowFoldEditor->text();
            }
            if( !mPcrDupBox->currentText().isEmpty() ){
                cmd = cmd + " -d " + mPcrDupBox->currentText();
            }
            if( !mAlignTypeBox->currentText().isEmpty() ){
                cmd = cmd + " -t " + mAlignTypeBox->currentText();
            }
            if( !mMinWindowSizeEditor->text().isEmpty() ){
                cmd = cmd + " -w " + mMinWindowSizeEditor->text();
            }
            if( !mNumProcEditor->text().isEmpty() ){
                cmd = cmd + " -p " + mNumProcEditor->text();
            }
        }

        accept();
        AnalysisManager::getAnalysisManager()->peakCalling( cmd, mOutputEditor->text() );
    }
}
