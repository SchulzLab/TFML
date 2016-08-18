/*********************************************************************
*
*   MODULE NAME:
*       MainWindow.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "PeakCallingDialog.hpp"
#include "ProjectDialog.hpp"
#include "TepicDialog.hpp"
#include "IntegrateDataDialog.hpp"
#include "DiffLearnDialog.hpp"
#include <iostream>
#include <string>
#include "DataManager.hpp"
#include "AnalysisManager.hpp"
#include <QtWebEngineWidgets/QtWebEngineWidgets>

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
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mUpdateLog( QString ) ), this, SLOT( updateLogText( QString ) ) );
    connect( mUi->mTabWidget, SIGNAL( tabCloseRequested( int ) ), this, SLOT( closeTab( int ) ) );
    connect( DataManager::getDataManager(), SIGNAL( processFinished( QString ) ), this, SLOT( handleLogFinished( QString ) ) );
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
    // File Menu
    QAction *newProject = new QAction( "&New project", this );
    QAction *addProject = new QAction( "&Open project", this );
    QAction *addAction = new QAction( tr( "&Open file" ), this );
    QAction *addBedAction = new QAction( "Open bed file", this );
    QAction *addDirAction = new QAction( "Open directory", this );
    QAction *quitAction = new QAction( tr( "&Quit" ), this );

    addAction->setShortcut( tr( "Ctrl+O" ) );
    quitAction->setShortcuts( QKeySequence::Quit );

    QMenu *fileMenu = mUi->mMenuBar->addMenu( tr( "&File" ) );
    fileMenu->addAction( newProject );
    fileMenu->addAction( addProject );
    fileMenu->addAction( addAction );
    fileMenu->addAction( addBedAction );
    fileMenu->addAction( addDirAction );
    fileMenu->addSeparator();
    fileMenu->addAction( quitAction );

    // Tools Menu
    QAction *peakCallingAction = new QAction( tr( "&Peak Calling" ), this );
    QAction *tepicAction = new QAction( tr( "&TEPIC" ), this );
    peakCallingAction->setShortcut( tr( "Ctrl+P" ) );
    tepicAction->setShortcut( tr( "Ctrl+T" ) );

    QMenu *toolsMenu = mUi->mMenuBar->addMenu( tr( "&Tools" ) );
    toolsMenu->addAction( peakCallingAction );
    toolsMenu->addAction( tepicAction );

    // Analyze Menu
    QAction *integrateAction = new QAction( "Integrate data", this );
    QAction *diffAction = new QAction( "Differentiate learning", this );
    QAction *regressionAction = new QAction( "Regression", this );

    QMenu *analyzeMenu = mUi->mMenuBar->addMenu( "Analyze" );
    analyzeMenu->addAction( integrateAction );
    analyzeMenu->addAction( diffAction );
    analyzeMenu->addAction( regressionAction );

    // Windows Menu
    QMenu *windowMenu = mUi->mMenuBar->addMenu( tr( "&Window" ) );
    QToolBar *fileTb = addToolBar("File list");
    QToolBar *resultTb = addToolBar("Result list");
    QToolBar *outputTb = addToolBar("Console output");
    QAction *fileListAction = fileTb->toggleViewAction();
    QAction *resultListAction = resultTb->toggleViewAction();
    QAction *outputAction = outputTb->toggleViewAction();
    if( DataManager::getDataManager()->getProjectName().isEmpty() ){
        addAction->setEnabled( false );
        addBedAction->setEnabled( false );
        addDirAction->setEnabled( false );
        toolsMenu->setEnabled( false );
        analyzeMenu->setEnabled( false );
    }
    windowMenu->addAction( fileListAction );
    windowMenu->addAction( resultListAction );
    windowMenu->addAction( outputAction );

    // Help Menu
    QAction *aboutQtAction = new QAction( tr( "About Qt" ), this );
    QMenu *helpMenu = mUi->mMenuBar->addMenu( tr( "&Help" ) );
    helpMenu->addAction(aboutQtAction);

    // Connect
    connect( newProject, SIGNAL( triggered( bool ) ), this, SLOT( newProject() ) );
    connect( addProject, SIGNAL( triggered( bool ) ), this, SLOT( addProject() ) );
    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( addBedAction, SIGNAL( triggered( bool ) ), this, SLOT( addBedFile() ) );
    connect( addDirAction, SIGNAL( triggered( bool ) ), this, SLOT( addDirectory() ) );
    connect( peakCallingAction, SIGNAL( triggered( bool ) ), this, SLOT( handlePeakCallingClicked() ) );
    connect( tepicAction, SIGNAL( triggered( bool ) ), this, SLOT( handleTepicClicked() ) );
    connect( integrateAction, SIGNAL( triggered( bool ) ), this, SLOT( handleIntegrateClicked() ) );
    connect( diffAction, SIGNAL( triggered( bool ) ), this, SLOT( handleDiffLearnClicked() ) );
    connect( regressionAction, SIGNAL( triggered( bool ) ), this, SLOT( handleRegressionClicked() ) );
    connect( fileListAction, SIGNAL( triggered( bool ) ), mUi->mDockLeft, SLOT( setVisible( bool ) ) );
    connect( mUi->mDockLeft, SIGNAL( visibilityChanged(bool)), fileListAction, SLOT( setChecked( bool ) ) );
    connect( resultListAction, SIGNAL( triggered( bool ) ), mUi->mDockResult, SLOT( setVisible( bool ) ) );
    connect( mUi->mDockResult, SIGNAL( visibilityChanged( bool ) ), resultListAction, SLOT( setChecked( bool ) ) );
    connect( outputAction, SIGNAL( triggered( bool ) ), mUi->mBottomDock, SLOT( setVisible( bool ) ) );
    connect( mUi->mBottomDock, SIGNAL( visibilityChanged( bool ) ), outputAction, SLOT( setChecked( bool ) ) );
    connect( quitAction, SIGNAL( triggered( bool ) ), this, SLOT( close() ) );
    connect( quitAction, SIGNAL( triggered( bool ) ), this, SLOT( close() ) );
    connect( aboutQtAction, SIGNAL( triggered( bool ) ), qApp, SLOT( aboutQt() ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), addAction, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), addBedAction, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), addDirAction, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), toolsMenu, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), analyzeMenu, SLOT( setEnabled( bool ) ) );

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
    QAction *refreshListAction = new QAction( "Refresh list", this );

    addAction->setIcon( QIcon::fromTheme( "document-open" ) );
    addDirectoryAction->setIcon( QIcon::fromTheme( "folder-open" ) );
    delAction->setIcon( QIcon::fromTheme( "edit-delete" ) );
    zoominAction->setIcon( QIcon::fromTheme( "zoom-in" ) );
    zoomoutAction->setIcon( QIcon::fromTheme( "zoom-out" ) );
    refreshAction->setIcon( QIcon::fromTheme( "view-refresh" ) );
    refreshListAction->setIcon( QIcon::fromTheme( "view-refresh" ) );
    staAction->setIcon( QIcon::fromTheme( "document-properties" ) );
    stopAction->setIcon( QIcon::fromTheme( "process-stop" ) );
    saveLogAction->setIcon( QIcon::fromTheme( "document-save" ) );

    toolBar->addAction( addAction );
    toolBar->addAction( addDirectoryAction );
    toolBar->addAction( delAction );
    toolBar->addAction( refreshListAction );
    toolBar->addAction( staAction );
    toolBar->addAction( zoominAction );
    toolBar->addAction( zoomoutAction );
    toolBar->addAction( stopAction );
    toolBar->addAction( saveLogAction );
    if( DataManager::getDataManager()->getProjectName().isEmpty() ){
        addAction->setEnabled( false );
        addDirectoryAction->setEnabled( false );
    }
    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( addDirectoryAction, SIGNAL( triggered( bool ) ), this, SLOT( addDirectory() ) );
    connect( delAction, SIGNAL( triggered( bool ) ), this, SLOT( delFile() ) );
    connect( delAction, SIGNAL( triggered( bool ) ), this, SLOT( delResultFile() ) );
    connect( staAction, SIGNAL( triggered( bool ) ), this, SLOT( analyzeFile() ) );
    connect( stopAction, SIGNAL( triggered( bool ) ), AnalysisManager::getAnalysisManager(), SLOT( killProcess() ) );
    connect( saveLogAction, SIGNAL( triggered( bool ) ), this, SLOT( saveLog() ) );
    connect( refreshListAction, SIGNAL( triggered( bool ) ), this, SLOT( refreshProject() ) );
    connect( zoominAction, SIGNAL( triggered( bool ) ), this, SLOT( zoomIn() ) );
    connect( zoomoutAction, SIGNAL( triggered( bool ) ), this, SLOT( zoomOut() ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), addDirectoryAction, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), addAction, SLOT( setEnabled( bool ) ) );
    connect( DataManager::getDataManager(), SIGNAL( hasActiveProject( bool ) ), staAction, SLOT( setEnabled( bool ) ) );
} // end of function MainWindow::createToolBar()

//---------------------------------------------------------------------------------
//! Create file list dock
//---------------------------------------------------------------------------------
void MainWindow::createFileListDock()
{
    mList = mUi->mFileList;
    mList->setContentsMargins( 9, 0, 0, 0 );
    mResultList = mUi->mResultFileList;
    mResultList->setContentsMargins( 9, 0, 0, 0 );
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mProcessOutputDone( QString ) ), this, SLOT( handleFinished( QString ) ) );
    connect( mList, SIGNAL( getFileFullPathName( QString ) ), this, SLOT( readFile( QString ) ) );
    connect( mResultList, SIGNAL( getFileFullPathName( QString ) ), this, SLOT( readFile( QString ) ) );
    mUi->mDockLeft->setWidget( mList );
    QString home = QDir().homePath();
    QString resultDir = home + "/Epigenetics_project/Result";

    //mResultList->addSubDirectory( resultDir );
} // end of function MainWindow::createFileListDock()

//---------------------------------------------------------------------------------
//! Create dialog to add file
//---------------------------------------------------------------------------------
void MainWindow::addFile()
{
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ) );
    if( fileName != "" ) {
        mList->addDirectory( fileName );
        DataManager::getDataManager()->addPath( fileName );
    }

} // end of function MainWindow::addFile()

//---------------------------------------------------------------------------------
//! Delete file in the file list
//---------------------------------------------------------------------------------
void MainWindow::delFile()
{
    QTreeWidgetItem *item = mList->getCurrentItem();
    if( item != NULL ){
        mList->delFile();
        DataManager::getDataManager()->delPath( item->text( 1 ) );
    }
    mResultList->clearFocus();
} // end of function MainWindow::delFile()

//---------------------------------------------------------------------------------
//! Delete file in the file list
//---------------------------------------------------------------------------------
void MainWindow::delResultFile()
{
    QTreeWidgetItem *item = mResultList->getCurrentItem();
    if( item != NULL ){
        mResultList->delFile();
        DataManager::getDataManager()->delResultPath( item->text( 1 ) );
    }

} // end of function MainWindow::delFile()

//---------------------------------------------------------------------------------
//! Create dialog to add bed file
//---------------------------------------------------------------------------------
void MainWindow::addBedFile()
{
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ), ".", tr("Bed Files(*.bed)") );
    if( fileName != "" ) {
        mList->addDirectory( fileName );
        DataManager::getDataManager()->addPath( fileName );
    }
} // end of function MainWindow::addBedFile()

//---------------------------------------------------------------------------------
//! Create dialog to add directory
//---------------------------------------------------------------------------------
void MainWindow::addDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory( this, tr( "Open Directory" ), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if( fileName != "" ) {
        mList->addDirectory( fileName );
        DataManager::getDataManager()->addPath( fileName );
    }
} // end of function MainWindow::addDirectory()

//---------------------------------------------------------------------------------
//! Handle peak calling clicked
//---------------------------------------------------------------------------------
void MainWindow::handlePeakCallingClicked()
{
    PeakCallingDialog *dialog = new PeakCallingDialog();
    dialog->exec();
} // end of function MainWindow::peakCalling()

//---------------------------------------------------------------------------------
//! Create peak calling dialog
//---------------------------------------------------------------------------------
void MainWindow::handleTepicClicked()
{
    TepicDialog *dialog = new TepicDialog();
    dialog->exec();
} // end of function MainWindow::handleTepicClicked()

//---------------------------------------------------------------------------------
//! Read file in the file list
//---------------------------------------------------------------------------------
void MainWindow::readFile
    (
    QString aFileName
    )
{
    QFileInfo info( aFileName );
    if( info.isDir() ){
        return;
    }
    //Check if the file already open
    for( int k = 0; k < mUi->mTabWidget->count(); k++ ) {
        if( mUi->mTabWidget->widget( k )->property( "tab_dir_fullpath" ).toString() == aFileName ) {
            mUi->mTabWidget->setCurrentIndex( k );
            return;
        }
    }

    QStringList tmp = aFileName.split("/");
    QString name = tmp[ tmp.length() - 1 ];
    QStringList nameSplit = name.split(".");
    name = nameSplit[ nameSplit.length() - 1 ];

    if( name == "jpg" || name == "png" ){
        readJpg( aFileName );
    }
    else if( name == "bed" || name == "narrowPeak" || name == "csv" ){
        readBed( aFileName );
    }
    else if( name == "html"){
        readHtmlFile( aFileName );
    }
    else{
        QFile file( aFileName );
        if( !file.exists() ){
            qDebug() << "NO existe el archivo "<< aFileName;
        }else{
            qDebug() << aFileName <<" encontrado...";
        }
        if( file.open( QIODevice::ReadOnly | QIODevice::Text ) ){
            QTableWidget* tableWidget = new QTableWidget();
            int row = 0;
            while( !file.atEnd() ){
                QByteArray line = file.readLine();
                QStringList colList = QString( line ).split( '\t' );
                if( tableWidget->rowCount() < row + 1 )
                    tableWidget->setRowCount( row );
                if( tableWidget->columnCount() < colList.size() )
                    tableWidget->setColumnCount( colList.size() );

                for( int column = 0; column < colList.size(); column++ )
                {
                    QTableWidgetItem *newItem = new QTableWidgetItem( colList.at( column ) );
                    newItem->setFlags( newItem->flags() ^ Qt::ItemIsEditable );
                    if( row == 0 ){
                        tableWidget->setHorizontalHeaderItem( column, newItem );
                    }
                    else{
                        tableWidget->setItem( row - 1, column, newItem );
                    }
                }
                row++;
            }
            file.close();
            tableWidget->setProperty( "tab_dir_fullpath", aFileName );
            tableWidget->resizeColumnsToContents();
            QStringList names = aFileName.split( "/" );
            QString fileName = names.value( names.length() - 1 );
            mUi->mTabWidget->addTab( tableWidget, fileName );
            mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
        }
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
    QLabel *label = new QLabel();
    QPixmap *pix = new QPixmap( aFileName );
    label->setPixmap( pix );
    label->show();
    label->setProperty( "tab_dir_fullpath", aFileName );
    QScrollArea *area = new QScrollArea();
    area->setWidget( label );
    QStringList names = aFileName.split( "/" );
    QString fileName = names.value( names.length() - 1 );

    mUi->mTabWidget->addTab( area, fileName );
    mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
} // end of function MainWindow::readJpg()

//---------------------------------------------------------------------------------
//! Read bed file
//---------------------------------------------------------------------------------
void MainWindow::readBed
    (
    QString aFileName
    )
{
    QFile file( aFileName );
    if( !file.exists() ){
        qDebug() << "NO existe el archivo "<< aFileName;
    }else{
        qDebug() << aFileName <<" encontrado...";
    }
    if( file.open( QIODevice::ReadOnly | QIODevice::Text ) ){
        QTableWidget* tableWidget = new QTableWidget();
        int row = 0;
        while( !file.atEnd() ){
            QByteArray line = file.readLine();
            QStringList colList = QString( line ).split( '\t' );
            if( tableWidget->rowCount() < row + 1 )
                tableWidget->setRowCount( row + 1);
            if( tableWidget->columnCount() < colList.size() )
                tableWidget->setColumnCount( colList.size() );

            for( int column = 0; column < colList.size(); column++ )
            {
                QTableWidgetItem *newItem = new QTableWidgetItem( colList.at( column ) );
                newItem->setFlags( newItem->flags() ^ Qt::ItemIsEditable );
                tableWidget->setItem( row, column, newItem );
            }
            row++;
        }
        file.close();
        tableWidget->setProperty( "tab_dir_fullpath", aFileName );
        tableWidget->resizeColumnsToContents();
        QStringList names = aFileName.split( "/" );
        QString fileName = names.value( names.length() - 1 );
        mUi->mTabWidget->addTab( tableWidget, fileName );
        mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
    }
} // end of function MainWindow::readBed()

//---------------------------------------------------------------------------------
//! Read html file
//---------------------------------------------------------------------------------
void MainWindow::readHtmlFile
    (
    QString aFileName
    )
{
    QWebEngineView *webView = new QWebEngineView();
    webView->load( QUrl( "file://" + aFileName ) );
    QStringList names = aFileName.split( "/" );
    QString fileName = names.value( names.length() - 1 );

    mUi->mTabWidget->addTab( webView, fileName );
    mUi->mTabWidget->setCurrentIndex( mUi->mTabWidget->count() - 1 );
} // end of function MainWindow::readHtml()

//---------------------------------------------------------------------------------
//! Save log file
//---------------------------------------------------------------------------------
void MainWindow::saveLog()
{
    DataManager::getDataManager()->saveLog( mUi->mLogText->toPlainText() );
} // end of function MainWindow::saveLog()

//---------------------------------------------------------------------------------
//! Handle log process finished
//---------------------------------------------------------------------------------
void MainWindow::handleLogFinished
    (
    QString aMsg
    )
{
    QMessageBox msgBox;
    msgBox.setText( aMsg );
    msgBox.exec();
} // end of function MainWindow::handleLogFinished()

//---------------------------------------------------------------------------------
//! Handle log process finished
//---------------------------------------------------------------------------------
void MainWindow::handleFinished
    (
    QString aPath
    )
{
    if( DataManager::getDataManager()->checkPath( aPath ) ){
        refreshProject();
    }
    else{
        mResultList->addDirectory( aPath );
    }
} // end of function MainWindow::handleFinished()

//---------------------------------------------------------------------------------
//! Create dialog to create project
//---------------------------------------------------------------------------------
void MainWindow::newProject()
{
    ProjectDialog *dialog = new ProjectDialog();
    dialog->exec();
    QString projectName = DataManager::getDataManager()->getProjectName();
    mList->delAll();
    mResultList->delAll();
    DataManager::getDataManager()->setActiveProject( projectName );
    mList->addProjectDirectory( projectName );
    mResultList->addProjectDirectory( projectName );
} // end of function MainWindow::newProject()

//---------------------------------------------------------------------------------
//! Create dialog to add
//---------------------------------------------------------------------------------
void MainWindow::addProject()
{
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select project file" ), DataManager::getDataManager()->getProjectHomePath(), tr("Project File(*.pro)") );
    if( fileName != "" ){
        QStringList name = fileName.split( "." );
        QString projectName = name[ 0 ];
        DataManager::getDataManager()->loadProject( fileName );
        QStringList fileList = DataManager::getDataManager()->getFileNameList();
        QStringList resultList = DataManager::getDataManager()->getResultFileNameList();
        name = projectName.split( "/" );
        projectName = name[ name.length() - 1 ];
        DataManager::getDataManager()->setActiveProject( projectName );
        mList->delAll();
        mList->addProjectDirectory( projectName );
        mResultList->delAll();
        mResultList->addProjectDirectory( projectName );
        for( int i = 0; i < fileList.length(); i++ ){
            mList->addDirectory( fileList.at( i ) );
        }
        for( int i = 0; i < resultList.length(); i++ ){
            mResultList->addDirectory( resultList.at( i ) );
        }
    }
} // end of function MainWindow::addProject()

//---------------------------------------------------------------------------------
//! Create dialog to add
//---------------------------------------------------------------------------------
void MainWindow::refreshProject()
{
    QString fileName = DataManager::getDataManager()->getProjectFilePath();
    QStringList name = fileName.split( "." );
    QString projectName = name[ 0 ];
    DataManager::getDataManager()->loadProject( fileName );
    QStringList fileList = DataManager::getDataManager()->getFileNameList();
    QStringList resultList = DataManager::getDataManager()->getResultFileNameList();
    name = projectName.split( "/" );
    projectName = name[ name.length() - 1 ];
    mList->delAll();
    mList->addProjectDirectory( projectName );
    mResultList->delAll();
    mResultList->addProjectDirectory( projectName );
    for( int i = 0; i < fileList.length(); i++ ){
        mList->addDirectory( fileList.at( i ) );
    }
    for( int i = 0; i < resultList.length(); i++ ){
        mResultList->addDirectory( resultList.at( i ) );
    }
} // end of function MainWindow::refreshProject()

//---------------------------------------------------------------------------------
//! Show dialog for integrating data
//---------------------------------------------------------------------------------
void MainWindow::handleIntegrateClicked()
{
    IntegrateDataDialog *dialog = new IntegrateDataDialog();
    dialog->exec();
} // end of function MainWindow::handleIntegrateClicked()

//---------------------------------------------------------------------------------
//! Show dialog for differentiating learning
//---------------------------------------------------------------------------------
void MainWindow::handleDiffLearnClicked()
{
    DiffLearnDialog *dialog = new DiffLearnDialog( DiffLearnDialog::DIFF_TYPE::DIFF );
    dialog->exec();
} // end of function MainWindow::handleDiffLearnClicked()

//---------------------------------------------------------------------------------
//! Show dialog for regression
//---------------------------------------------------------------------------------
void MainWindow::handleRegressionClicked()
{
    DiffLearnDialog *dialog = new DiffLearnDialog( DiffLearnDialog::DIFF_TYPE::REGRESSION );
    dialog->exec();
} // end of function MainWindow::handleRegressionClicked()

//---------------------------------------------------------------------------------
//! Zoom in
//---------------------------------------------------------------------------------
void MainWindow::zoomIn()
{
    QWidget *widget = mUi->mTabWidget->widget( mUi->mTabWidget->currentIndex() );
    QString name = mUi->mTabWidget->tabText( mUi->mTabWidget->currentIndex() );
    QStringList nameSplit = name.split(".");
    name = nameSplit[ nameSplit.length() - 1 ];
    if( name == "html"){
        QWebEngineView *view = ( QWebEngineView* ) widget;
        view->setZoomFactor( view->zoomFactor() + 0.2 );
    }
} // end of function MainWindow::zoomIn()

//---------------------------------------------------------------------------------
//! Zoom in
//---------------------------------------------------------------------------------
void MainWindow::zoomOut()
{
    QWidget *widget = mUi->mTabWidget->widget( mUi->mTabWidget->currentIndex() );
    QString name = mUi->mTabWidget->tabText( mUi->mTabWidget->currentIndex() );
    QStringList nameSplit = name.split(".");
    name = nameSplit[ nameSplit.length() - 1 ];
    if( name == "html"){
        QWebEngineView *view = ( QWebEngineView* ) widget;
        view->setZoomFactor( view->zoomFactor() - 0.2 );
    }
} // end of function MainWindow::zoomOut()
