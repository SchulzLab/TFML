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

    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( mTree );
    setLayout( layout );
    mTree->setFocusPolicy( Qt::TabFocus );
    connect( mTree, SIGNAL( itemDoubleClicked( QTreeWidgetItem*, int ) ), this, SLOT( doubleClickedEvent( QTreeWidgetItem*, int ) ) );
    connect( mTree, SIGNAL( itemClicked( QTreeWidgetItem*, int ) ), this, SLOT( clickedEvent( QTreeWidgetItem*, int ) ) );
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
    dirFile.setSorting( QDir::Name );
    QFileInfoList listFile = dirFile.entryInfoList();
    for( int i = 0; i < listFile.size(); ++i ) {
        QFileInfo fileInfo = listFile.at( i );
        QString fileName = fileInfo.fileName();
        QString pathName = fileInfo.absoluteFilePath();
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

         QTreeWidgetItem* childRoot = new QTreeWidgetItem( QStringList() << fileName << pathName );
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
            QStringList path = aPath.split( "/" );
            QString name = path[ path.length() - 1 ];
            QTreeWidgetItem *root = new QTreeWidgetItem( QStringList() << name << aPath );
            root->setToolTip( 0, aPath );
            mRoot->addChild( root );
            allfile( root, aPath );
        }
        else if( s.st_mode & S_IFREG )
        {
            QStringList path = aPath.split( "/" );
            QString name = path[ path.length() - 1 ];
            QTreeWidgetItem *root = new QTreeWidgetItem( QStringList() << name << aPath );
            root->setToolTip( 1, aPath );
            mRoot->addChild( root );
        }
    }
} // end of function FileListWidget::addDirectory()

//---------------------------------------------------------------------------------
//! Add file or directory in subdirectory
//---------------------------------------------------------------------------------
void FileListWidget::addSubDirectory
    (
    QString aPath
    )
{
    QDir dir( aPath );
    QFileInfoList list = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );
    for( int i = 0; i < list.size(); i++ ){
        addDirectory( list.at( i ).absoluteFilePath() );
    }
} // end of function FileListWidget::addSubDirectory()

//---------------------------------------------------------------------------------
//! Delete file or directory
//---------------------------------------------------------------------------------
void FileListWidget::delFile()
{
    qInfo() << mTree->selectedItems().length();
    QTreeWidgetItem *item = mTree->selectedItems().at( 0 );
    mTree->removeItemWidget(item, 1);
    //mRoot->removeChild( item );
} // end of function FileListWidget::delFile()

void FileListWidget::DeleteItem(QTreeWidgetItem *item) {
  if (!item) return;
  for(int i=item->childCount()-1; i>=0; i--) {
    DeleteItem(item->child(i));
  }
  delete item;
}

//---------------------------------------------------------------------------------
//! Delete all file or directory
//---------------------------------------------------------------------------------
void FileListWidget::delAll()
{
    mTree->clear();
} // end of function FileListWidget::delFile()

//---------------------------------------------------------------------------------
//! Get current item in filelist
//---------------------------------------------------------------------------------
QTreeWidgetItem* FileListWidget::getCurrentItem()
{
   return mTree->currentItem();
} // end of function FileListWidget::getCurrentItem()

//---------------------------------------------------------------------------------
//! Handel click event
//---------------------------------------------------------------------------------
void FileListWidget::clickedEvent
    (
    QTreeWidgetItem *aItem,
    int aNumber
    )
{
    QStringList list;
    list.append( aItem->text( 0 ) );
    list.append( aItem->text( 1 ) );
    if( !list.isEmpty() ){
        getFileName( list  );
    }
} // end of function FileListWidget::clickedEvent()

//---------------------------------------------------------------------------------
//! Handel double click event
//---------------------------------------------------------------------------------
void FileListWidget::doubleClickedEvent
    (
    QTreeWidgetItem *aItem,
    int aNumber
    )
{
    QString fileName = aItem->text( 1 );
    if( !fileName.isEmpty() ){
        getFileFullPathName( fileName );
    }
} // end of function FileListWidget::clickedEvent()

//---------------------------------------------------------------------------------
//! Get current item in filelist
//---------------------------------------------------------------------------------
QTreeWidget* FileListWidget::getTree()
{
   return mTree;
} // end of function FileListWidget::getTree()

//---------------------------------------------------------------------------------
//! Add project directory
//---------------------------------------------------------------------------------
void FileListWidget::addProjectDirectory
    (
    QString aPath
    )
{
    mRoot = new QTreeWidgetItem( mTree, QStringList() << aPath << aPath );
    mRoot->setToolTip( 0, aPath );
    mRoot->setCheckState( 1, Qt::Checked );
    mRoot->setExpanded( true );
} // end of function FileListWidget::addDirectory()
