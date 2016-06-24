#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedialog.h"
#include "peakcallingdialog.h"
#include <iostream>
#include <string>
#include "datamanager.h"
#include "treewidget.h"
#include "analysismanager.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    qInfo() << "MainWindow::MainWindow()";
    mUi->setupUi( this );
    createMenuBar();
    createFileListDock();
    createToolBar();
    //createAnalysisDock();
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mUpdateLog( QString, QString ) ), this, SLOT( updateLogText( QString,QString ) ) );
    connect( mUi->mTabWidget, SIGNAL( tabCloseRequested( int ) ), this, SLOT( closeTab( int ) ) );
    mUi->textEdit->setAlignment(Qt::AlignCenter);
    setWindowTitle( "Epigenetics analysis tool" );
}

MainWindow::~MainWindow()
{
    delete mUi;
}


void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction( tr( "&Open file" ), this );
    QAction *addBedAction = new QAction( "Open bed file", this );
    QAction *addDirAction = new QAction( "Open directory", this );
    QAction *quitAction = new QAction(tr( "&Quit" ), this );
    QAction *aboutAction = new QAction(tr( "&About us"), this );
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

    QMenu *helpMenu = mUi->mMenuBar->addMenu( tr( "&Help" ) );
    //helpMenu->addAction(aboutAction);
    //helpMenu->addAction(aboutQtAction);

    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( addBedAction, SIGNAL( triggered( bool ) ), this, SLOT( addBedFile() ) );
    connect( addDirAction, SIGNAL( triggered( bool ) ), this, SLOT( addDirectory() ) );
    connect( peakCallingAction, SIGNAL( triggered( bool ) ), this, SLOT( peakCalling() ) );
    connect( quitAction, SIGNAL( triggered( bool ) ), this, SLOT( close() ) );

    /*
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    */
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = mUi->mMainToolBar;
    QAction *addAction = new QAction( tr( "&Add" ), this );
    QAction *staAction = new QAction( tr( "&Analze" ), this );
    addAction->setIcon( QIcon::fromTheme( "document-open" ) );
    staAction->setIcon( QIcon::fromTheme( "document-properties" ) );
    toolBar->addAction( addAction );
    toolBar->addAction( staAction );
    connect( addAction, SIGNAL( triggered( bool ) ), this, SLOT( addFile() ) );
    connect( staAction, SIGNAL( triggered( bool ) ), this, SLOT( analyzeFile() ) );
}

void MainWindow::createAnalysisDock()
{
    mDockRight = new QDockWidget( tr( "Analysis Tools" ), this );
    mDockRight->setMinimumWidth( 300 );
    addDockWidget( Qt::RightDockWidgetArea, mDockRight );
}

void MainWindow::createFileListDock()
{
    mList = mUi->mFileList;
    connect( AnalysisManager::getAnalysisManager(), SIGNAL( mProcessOutputDone( QString ) ), mList, SLOT( addDirectory( QString ) ) );
    //connect( AnalysisManager::getAnalysisManager(), SIGNAL( receiveFinished( QString ) ), mList, SLOT( addDirectory( QString ) ) );
    connect( mList, SIGNAL( readFile( QString ) ), this, SLOT(readFile(QString)));
    mUi->mDockLeft->setWidget( mList );
}

void MainWindow::addFile()
{
    std::cout << QDir::currentPath().toStdString() << endl;
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ) );
    if( fileName != "" ) {
        qInfo() << "MainWindow::openFile()";
        mList->addDirectory( fileName );
    }
}

void MainWindow::addBedFile()
{
    std::cout << QDir::currentPath().toStdString() << endl;
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName( this, tr( "select file" ), ".", tr("Bed Files(*.bed)") );
    if( fileName != "" ) {
        qInfo() << "MainWindow::openBedFile()";
        mList->addDirectory( fileName );
    }
}

void MainWindow::addDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(fileName != "") {
        qInfo() << "MainWindow::openFile()";
        mList->addDirectory(fileName);
    }
}

void MainWindow::peakCalling()
{
    PeakCallingDialog *dialog = new PeakCallingDialog();
    dialog->exec();
}

void MainWindow::readFile( QString aFileName )
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
        textEdit->setReadOnly( true );
        textEdit->setTextInteractionFlags( Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard );
    }
}

void MainWindow::updateLogText( QString aStdErr, QString aStdOut )
{
    //mUi->mLogText->append( aStdOut );
    //mUi->mLogText->append( aStdErr );
}

void MainWindow::closeTab(int aIndex)
{
    mUi->mTabWidget->removeTab( aIndex );
}

void MainWindow::analyzeFile()
{
    QTreeWidgetItem *item = mList->getCurrentItem();
    if( item != NULL ){
        AnalysisManager::getAnalysisManager()->analyseBedFile( item->text( 1 ) );
    }
}

void MainWindow::readJpg( QString aFileName ){

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
}
