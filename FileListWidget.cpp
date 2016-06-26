/*********************************************************************
*
*   MODULE NAME:
*       FileListWidget.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "FileListWidget.hpp"
#include "AnalysisManager.hpp"
#include "DataManager.hpp"
#include <sys/stat.h>

#define COLUMN_COUNT 1

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
FileListWidget::FileListWidget
    (
    QWidget *widget
    )
{
    QVBoxLayout *layout = new QVBoxLayout();
    mTree = new QTreeWidget( this );
    mTree->setColumnCount( COLUMN_COUNT );
    mTree->setHeaderHidden( true );

    /* For the test */
    QTreeWidgetItem *root = new QTreeWidgetItem( mTree, QStringList( "result" ) );
    allfile( root, "peak_call_result" );
    /////////////////////

    layout->setContentsMargins( 9, 0, 0, 0 );
    layout->addWidget( mTree );
    setLayout( layout );

    connect( mTree, SIGNAL( itemDoubleClicked( QTreeWidgetItem*, int ) ), this, SLOT( clickedEvent( QTreeWidgetItem*, int ) ) );
} // end of function FileListWidget::FileListWidget()

//---------------------------------------------------------------------------------
//! Add all files and sub-directories
//---------------------------------------------------------------------------------
QFileInfoList FileListWidget::allfile
    (
    QTreeWidgetItem *aRoot,
    QString aPath
    )
{
    QDir dir( aPath );
    QDir dirFile( aPath );
    dirFile.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
    //dir_file.setNameFilters(filters);

    dirFile.setSorting(QDir::Name);
    QFileInfoList listFile = dirFile.entryInfoList();
    for( int i = 0; i < listFile.size(); ++i ) {
        QFileInfo fileInfo = listFile.at( i );
        QString fileName = fileInfo.fileName();
        QString pathName = fileInfo.absoluteFilePath();
        qInfo() << fileInfo.absoluteFilePath() << fileInfo.fileName();
        QTreeWidgetItem* child = new QTreeWidgetItem( QStringList() << fileName << pathName );
        child->setToolTip( 0, pathName );
        child->setCheckState( 1, Qt::Checked );
        aRoot->addChild( child );
    }

    QFileInfoList fileList = dir.entryInfoList( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
    QFileInfoList folderList = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );

    for( int i = 0; i != folderList.size(); i++ )
    {
         QString pathName = folderList.at( i ).absoluteFilePath();
         QFileInfo folderInfo = folderList.at( i );
         QString fileName = folderInfo.fileName();

         QTreeWidgetItem* childRoot = new QTreeWidgetItem( QStringList() << fileName );
         childRoot->setToolTip( 0, pathName );
         //childroot->setIcon(0, QIcon("./Resources/images/file.png"));
         childRoot->setCheckState( 1, Qt::Checked );
         aRoot->addChild( childRoot );
         QFileInfoList childFileList = allfile( childRoot, pathName );
         fileList.append( childFileList );
         fileList.append( fileName );
    }
    return fileList;
} // end of function FileListWidget::allfile()

//---------------------------------------------------------------------------------
//! Add file or directory
//---------------------------------------------------------------------------------
void FileListWidget::addDirectory
    (
    QString aPath
    )
{
    struct stat s;
    QByteArray array = aPath.toLocal8Bit();
    char* buffer = array.data();
    if( stat( buffer, &s ) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            qInfo() << " FileListWidget::addDirectory";
            QStringList path = aPath.split( "/" );
            QString name = path[ path.length() - 1 ];
            QTreeWidgetItem *root = new QTreeWidgetItem( mTree, QStringList() << name << aPath );
            root->setToolTip( 0, aPath );
            allfile( root, aPath );
        }
        else if( s.st_mode & S_IFREG )
        {
            qInfo() << " FileListWidget::addFile";
            QStringList path = aPath.split( "/" );
            QString name = path[ path.length() - 1 ];
            QTreeWidgetItem *root = new QTreeWidgetItem( mTree, QStringList() << name << aPath );
            root->setToolTip( 1, aPath );
        }
    }
} // end of function FileListWidget::addDirectory()

//---------------------------------------------------------------------------------
//! Delete file or directory
//---------------------------------------------------------------------------------
void FileListWidget::delFile()
{
    qDeleteAll(mTree->selectedItems());
} // end of function FileListWidget::delFile()

//---------------------------------------------------------------------------------
//! Get current item in filelist
//---------------------------------------------------------------------------------
QTreeWidgetItem* FileListWidget::getCurrentItem()
{
   return mTree->currentItem();
} // end of function FileListWidget::getCurrentItem()

//---------------------------------------------------------------------------------
//! Handel double click event
//---------------------------------------------------------------------------------
void FileListWidget::clickedEvent
    (
    QTreeWidgetItem *aItem,
    int aNumber
    )
{
    QString fileName = aItem->text( 1 );
    qInfo() << fileName;
    if( !fileName.isEmpty() ){
        readFile( fileName );
    }
} // end of function FileListWidget::clickedEvent()
