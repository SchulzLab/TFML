/*********************************************************************
*
*   MODULE NAME:
*       ProjectDialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "DataManager.hpp"
#include "AnalysisManager.hpp"
#include <iostream>
#include "ProjectDialog.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
ProjectDialog::ProjectDialog
    (
    QWidget *parent
    )
    : QDialog( parent )
{
    init();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( mInputWidget );
    setMinimumWidth( 600 );
    setLayout( layout );
    setWindowTitle( "Set project name" );

} // end of function ProjectDialog::ProjectDialog()

//---------------------------------------------------------------------------------
//! Init
//---------------------------------------------------------------------------------
void ProjectDialog::init()
{
    mFileLabel = new QLabel();
    mDirLabel = new QLabel();
    mDirNameLabel = new QLabel();
    mFileLabel->setText( "Name:" );
    mDirLabel->setText( "Create in:" );
    mFileEdit = new QLineEdit();
    QString homePath = DataManager::getDataManager()->getProjectHomePath();
    mDirNameLabel->setText( homePath );
    mInputWidget = createInputWidgets();

} // end of function ProjectDialog::init()

//---------------------------------------------------------------------------------
//! Create basic input widgets
//---------------------------------------------------------------------------------
QGroupBox *ProjectDialog::createInputWidgets()
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
    layout->addWidget( mDirLabel, 1, 0 );
    layout->addWidget( mDirNameLabel, 1, 1, 1, 20, 0 );
    layout->addWidget( cancelButton, 1, 21 );
    box->setLayout( layout );

    return box;
} // end of function ProjectDialog::createInputWidgets()

//---------------------------------------------------------------------------------
//! Handle click ok
//---------------------------------------------------------------------------------
void ProjectDialog::handleClickOk()
{
    if( !mFileEdit->text().isEmpty() ){
        if( DataManager::getDataManager()->createProjectDir( mFileEdit->text() ) ){
            accept();
        }
    }
} // end of function ProjectDialog::ok()

//---------------------------------------------------------------------------------
//! Handel click event
//---------------------------------------------------------------------------------
void ProjectDialog::handleCancelClick()
{
    close();
} // end of function ProjectDialog::handleClick()
