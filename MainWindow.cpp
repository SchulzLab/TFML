/*********************************************************************
*
*   MODULE NAME:
*       MainWindow.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "PeakCallingDialog.hpp"
#include <iostream>
#include <string>
#include "DataManager.hpp"
#include "AnalysisManager.hpp"

using namespace std;

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
MainWindow::MainWindow
    (
    QWidget *parent
    )
    : QMainWindow( parent )
    , mUi( new Ui::MainWindow )
{
    qInfo() << "MainWindow::MainWindow()";
    mUi->setupUi( this );
    createMenuBar();
    createFileListDock();
    createToolBar();
    //createAnalysisDock();
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mUpdateLog( QString ) ), this, SLOT( updateLogText( QString ) ) );
    connect( mUi->mTabWidget, SIGNAL( tabCloseRequested( int ) ), this, SLOT( closeTab( int ) ) );
    mUi->textEdit->setAlignment(Qt::AlignCenter);
    setWindowTitle( "Epigenetics analysis tool" );
} // end of function MainWindow::MainWindow()

MainWindow::~MainWindow()
{
    delete mUi;
} // end of function MainWindow::~MainWindow()

//---------------------------------------------------------------------------------
//! Create menu bar and init menu item
//---------------------------------------------------------------------------------
void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction( tr( "&Open file" ), this );
    QAction *addBedAction = new QAction( "Open bed file", this );
    QAction *addDirAction = new QAction( "Open directory", this );
    QAction *quitAction = new QAction(tr( "&Quit" ), this );
    QAction *peakCallingAction = new QAction( tr( "&Peak Calling" ), this );
    addAction->setShortcut( tr( "Ctrl+O" ) );
    quitAction->setShortcuts( QKeySequence::Quit );

    //QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu *fileMenu = mUi->mMenuBar->addMenu( tr( "&File" ) );
    fileMenu->addAction( addAction );
    fileMenu->addAction( addBedAction );
    fileMenu->addAction( addDirAction );
    fileMenu->addSeparator();
    fileMenu->addAction( quitAction );

    QMenu *toolsMenu = mUi->mMenuBar->addMenu( tr( "&Tools" ) );
    toolsMenu->addAction( peakCallingAction );

    QMenu *windowMenu = mUi->mMenuBar->addMenu( tr( "&Window" ) );
    QToolBar *fileTb = addToolBar("File list");
    QToolBar *resultTb = addToolBar("Result list");
    QToolBar *outputTb = addToolBar("Console output");
    QAction *fileListAction = fileTb->toggleViewAction();
    QAction *resultListAction = resultTb->toggleViewAction();
    QAction *outputAction = outputTb->toggleViewAction();

    windowMenu->addAction( fileListAction );
    windowMenu->addAction( resultListAction );
    windowMenu->addAction( outputAction );

    QMenu *helpMenu = mUi->mMenuBar->addMenu( tr( "&Help" ) );
    //helpMenu->addAction(aboutAction);
    //helpMenu->addAction(aboutQtAction);

    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( addBedAction, SIGNAL( triggered( bool ) ), this, SLOT( addBedFile() ) );
    connect( addDirAction, SIGNAL( triggered( bool ) ), this, SLOT( addDirectory() ) );
    connect( peakCallingAction, SIGNAL( triggered( bool ) ), this, SLOT( peakCalling() ) );
    connect( fileListAction, SIGNAL( triggered( bool ) ), mUi->mDockLeft, SLOT( setVisible( bool ) ) );
    connect( mUi->mDockLeft, SIGNAL( visibilityChanged(bool)), fileListAction, SLOT( setChecked(bool) ) );
    connect( resultListAction, SIGNAL( triggered( bool ) ), mUi->mDockResult, SLOT( setVisible( bool ) ) );
    connect( mUi->mDockResult, SIGNAL( visibilityChanged(bool)), resultListAction, SLOT( setChecked(bool) ) );
    connect( outputAction, SIGNAL( triggered( bool ) ), mUi->mBottomDock, SLOT( setVisible( bool ) ) );
    connect( mUi->mBottomDock, SIGNAL( visibilityChanged(bool)), outputAction, SLOT( setChecked(bool) ) );
    connect( quitAction, SIGNAL( triggered( bool ) ), this, SLOT( close() ) );
    /*
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
   */
} // end of function MainWindow::createMenuBar()

//---------------------------------------------------------------------------------
//! Create tool bar and init tool
//---------------------------------------------------------------------------------
void MainWindow::createToolBar()
{
    QToolBar *toolBar = mUi->mMainToolBar;

    QAction *addAction = new QAction( "Add file", this );
    QAction *addDirectoryAction = new QAction( "Add directory", this );
    QAction *delAction = new QAction( "Delete", this );
    QAction *staAction = new QAction( "Analyze", this );
    QAction *refreshAction = new QAction( "Refresh", this );
    QAction *zoominAction = new QAction( "Zoom in", this );
    QAction *zoomoutAction = new QAction( "Zoom out", this );
    QAction *stopAction = new QAction( "Stop", this );
    QAction *saveLogAction = new QAction( "Save log", this );

    addAction->setIcon( QIcon::fromTheme( "document-open" ) );
    addDirectoryAction->setIcon( QIcon::fromTheme( "folder-open" ) );
    delAction->setIcon( QIcon::fromTheme( "edit-delete" ) );
    zoominAction->setIcon( QIcon::fromTheme( "zoom-in" ) );
    zoomoutAction->setIcon( QIcon::fromTheme( "zoom-out" ) );
    refreshAction->setIcon( QIcon::fromTheme( "view-refresh" ) );
    staAction->setIcon( QIcon::fromTheme( "document-properties" ) );
    stopAction->setIcon( QIcon::fromTheme( "process-stop" ) );
    saveLogAction->setIcon( QIcon::fromTheme( "document-save" ) );

    toolBar->addAction( addAction );
    toolBar->addAction( addDirectoryAction );
    toolBar->addAction( delAction );
    toolBar->addAction( refreshAction );
    toolBar->addAction( staAction );
    toolBar->addAction( zoominAction );
    toolBar->addAction( zoomoutAction );
    toolBar->addAction( stopAction );
    toolBar->addAction( saveLogAction );

    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( addDirectoryAction, SIGNAL( triggered( bool ) ), this, SLOT( addDirectory() ) );
    connect( delAction, SIGNAL( triggered( bool ) ), this, SLOT( delFile() ) );
    connect( staAction, SIGNAL( triggered( bool ) ), this, SLOT( analyzeFile() ) );
    connect( stopAction, SIGNAL( triggered( bool ) ), AnalysisManager::getAnalysisManager(), SLOT( killProcess() ) );
    connect( saveLogAction, SIGNAL( triggered( bool ) ), this, SLOT( saveLog() ) );

} // end of function MainWindow::createToolBar()

//---------------------------------------------------------------------------------
//! Create file list dock
//---------------------------------------------------------------------------------
void MainWindow::createFileListDock()
{
    mList = mUi->mFileList;
    mResultList = mUi->mResultFileList;
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mProcessOutputDone( QString ) ), mResultList, SLOT( addDirectory( QString ) ) );
    connect( mList, SIGNAL( readFile( QString ) ), this, SLOT( readFile( QString ) ) );
    connect( mResultList, SIGNAL( readFile( QString ) ), this, SLOT( readFile( QString ) ) );
    mUi->mDockLeft->setWidget( mList );
} // end of function MainWindow::createFileListDock()

//---------------------------------------------------------------------------------
//! Create dialog to add file
//---------------------------------------------------------------------------------
void MainWindow::addFile()
{
    std::cout << QDir::currentPath().toStdString() << endl;
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ) );
    if( fileName != "" ) {
        qInfo() << "MainWindow::openFile()";
        mList->addDirectory( fileName );
    }

} // end of function MainWindow::addFile()

//---------------------------------------------------------------------------------
//! Delete file in the file list
//---------------------------------------------------------------------------------
void MainWindow::delFile()
{
    QTreeWidgetItem *item = mList->getCurrentItem();
    if( item != NULL ){
        qInfo() << "MainWindow::delFile()";
        mList->delFile();
    }

} // end of function MainWindow::delFile()

//---------------------------------------------------------------------------------
//! Create dialog to add bed file
//---------------------------------------------------------------------------------
void MainWindow::addBedFile()
{
    std::cout << QDir::currentPath().toStdString() << endl;
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ), ".", tr("Bed Files(*.bed)") );
    if( fileName != "" ) {
        qInfo() << "MainWindow::openBedFile()";
        mList->addDirectory( fileName );
    }
} // end of function MainWindow::addBedFile()

//---------------------------------------------------------------------------------
//! Create dialog to add directory
//---------------------------------------------------------------------------------
void MainWindow::addDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory( this, tr( "Open Directory" ), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if( fileName != "" ) {
        qInfo() << "MainWindow::openFile()";
        mList->addDirectory( fileName );
    }
} // end of function MainWindow::addDirectory()

//---------------------------------------------------------------------------------
//! Create peak calling dialog
//---------------------------------------------------------------------------------
void MainWindow::peakCalling()
{
    PeakCallingDialog *dialog = new PeakCallingDialog();
    dialog->exec();
} // end of function MainWindow::peakCalling()

//---------------------------------------------------------------------------------
//! Read file in the file list
//---------------------------------------------------------------------------------
void MainWindow::readFile
    (
    QString aFileName
    )
{
    //Check if the file already open
    for( int k = 0; k < mUi->mTabWidget->count(); k++ ) {
        if( mUi->mTabWidget->widget( k )->property( "tab_dir_fullpath" ).toString() == aFileName ) {
            mUi->mTabWidget->setCurrentIndex( k );
            return;
        }
    }

    QFile file( aFileName );
    if( !file.exists() ){
        qDebug() << "NO existe el archivo "<< aFileName;
    }else{
        qDebug() << aFileName <<" encontrado...";
    }

    QStringList tmp = aFileName.split("/");
    QString name = tmp[ tmp.length() - 1 ];
    QStringList nameSplit = name.split(".");
    name = nameSplit[ nameSplit.length() - 1 ];

    if( name == "jpg"){
        readJpg( aFileName );
    }
    else{
        QTextEdit *textEdit = new QTextEdit();
        QString content;
        textEdit->clear();
        if( file.open( QIODevice::ReadOnly | QIODevice::Text ) ){
            QTextStream stream( &file );
            while ( !stream.atEnd() ){
                content = stream.readAll();
                textEdit->setText( textEdit->toPlainText() + content );
            }
        }
        file.close();
        textEdit->setProperty( "tab_dir_fullpath", aFileName );

        QStringList names = aFileName.split( "/" );
        QString fileName = names.value( names.length() - 1 );
        mUi->mTabWidget->addTab( textEdit, fileName );
        mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
        //textEdit->sets
        textEdit->setReadOnly( true );
        textEdit->setTextInteractionFlags( Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard );
    }
} // end of function MainWindow::readFile()

//---------------------------------------------------------------------------------
//! Update log text
//---------------------------------------------------------------------------------
void MainWindow::updateLogText
    (
    QString aLog
    )
{
    mUi->mLogText->append( aLog );
} // end of function MainWindow::updateLogText()

//---------------------------------------------------------------------------------
//! Close tab in tab widget
//---------------------------------------------------------------------------------
void MainWindow::closeTab
    (
    int aIndex
    )
{
    mUi->mTabWidget->removeTab( aIndex );
} // end of function MainWindow::closeTab()

//---------------------------------------------------------------------------------
//! Analyze file and output pic and statstic data file
//---------------------------------------------------------------------------------
void MainWindow::analyzeFile()
{
    QTreeWidgetItem *item = mList->getCurrentItem();
    if( item != NULL ){
        AnalysisManager::getAnalysisManager()->analyseBedFile( item->text( 1 ) );
    }
} // end of function MainWindow::analyzeFile()

//---------------------------------------------------------------------------------
//! Read jpg file
//---------------------------------------------------------------------------------
void MainWindow::readJpg
    (
    QString aFileName
    )
{

    qInfo() << "loading jpg";
    QLabel *label = new QLabel();

    label->setPixmap( aFileName );
    label->show();

    label->setProperty( "tab_dir_fullpath", aFileName );
    QScrollArea *area = new QScrollArea();
    area->setWidget(label);
    QStringList names = aFileName.split( "/" );
    QString fileName = names.value( names.length() - 1 );
    mUi->mTabWidget->addTab( area, fileName );
    mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
} // end of function MainWindow::readJpg()

//---------------------------------------------------------------------------------
//! Save log file
//---------------------------------------------------------------------------------
void MainWindow::saveLog()
{
    DataManager::getDataManager()->saveLog( mUi->mLogText->toPlainText() );
} // end of function MainWindow::saveLog()
