/*********************************************************************
*
*   MODULE NAME:
*       FileDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "AnalysisManager.hpp"
#include <iostream>
#include "FileDialog.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
FileDialog::FileDialog
    (
    int aSelectType,
    QWidget *parent
    )
    : QDialog( parent )
{
    mType = aSelectType;
    init();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( mFileList );
    layout->addWidget( mInputWidget );
    setMinimumWidth( 600 );
    setLayout( layout );

} // end of function FileDialog::FileDialog()

//---------------------------------------------------------------------------------
//! Init
//---------------------------------------------------------------------------------
void FileDialog::init()
{
    mTypeComboBox = new QComboBox();
    mFileLabel = new QLabel();
    mTypeLabel = new QLabel();
    if( mType == SELECT_TYPE::FILE ){
        mFileLabel->setText( "File name:" );
        mTypeLabel->setText( "Type:" );
        mTypeComboBox->addItem( "All file(*)" );
        setWindowTitle( "Select file" );
    }
    else if( mType == SELECT_TYPE::DIR ){
        mFileLabel->setText( "Directory:" );
        mTypeLabel->setText( "Type:" );
        mTypeComboBox->addItem( "directory" );
        mTypeComboBox->setDisabled( true );
        setWindowTitle( "Select directory" );
    }

    mFileName = "";
    mFileEdit = new QLineEdit();
    mFileEdit->setReadOnly( true );
    mFileList = new FileListWidget( this );
    mFileList->initListType( FileListWidget::LIST_TYPE::FILE_LIST );
    QStringList list = DataManager::getDataManager()->getFileNameList();
    mInputWidget = createInputWidgets();
    mFileList->addProjectDirectory( DataManager::getDataManager()->getProjectName() );
    for( int i = 0; i < list.length(); i++ ){
        mFileList->addDirectory( list[ i ] );
    }
    connect( mFileList, SIGNAL( getFileName( QStringList ) ), this, SLOT( handleClick( QStringList ) ) );

} // end of function FileDialog::init()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *FileDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox();
    QGridLayout *layout = new QGridLayout;
    QPushButton *cancelButton = new QPushButton( tr( "&Cancel" ) );
    QPushButton *okButton = new QPushButton( tr( "&OK" ) );

    cancelButton->setDefault( true );

    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( handleCancelClick() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( handleClickOk() ) );


    layout->addWidget( mFileLabel, 0, 0 );
    layout->addWidget( mFileEdit, 0, 1, 1, 20, 0 );
    layout->addWidget( okButton, 0, 21 );
    layout->addWidget( mTypeLabel, 1, 0 );
    layout->addWidget( mTypeComboBox, 1, 1, 1, 20, 0 );
    layout->addWidget( cancelButton, 1, 21 );
    box->setLayout( layout );

    return box;
} // end of function FileDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void FileDialog::handleClickOk()
{
    qInfo() << mFileName;
    if( !mFileEdit->text().isEmpty() ){
        if( mType == SELECT_TYPE::DIR ){
            QFileInfo info( mFileName );
            if( info.isDir() ){
                accept();
            }
        }
        else{
            accept();
        }
    }
} // end of function FileDialog::ok()

//---------------------------------------------------------------------------------
//! Get fileName
//---------------------------------------------------------------------------------
QString FileDialog::getFileName()
{
    return mFileName;
} // end of function FileDialog::ok()

//---------------------------------------------------------------------------------
//! Handel click event
//---------------------------------------------------------------------------------
void FileDialog::handleClick
    (
    QStringList aFileName
    )
{
    mFileEdit->setText( aFileName[ 0 ] );
    mFileName = aFileName[ 1 ];
} // end of function FileDialog::handleClick()

//---------------------------------------------------------------------------------
//! Handel click event
//---------------------------------------------------------------------------------
void FileDialog::handleCancelClick()
{
    mFileName = "";
    close();
} // end of function FileDialog::handleClick()
