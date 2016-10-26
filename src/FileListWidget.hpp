/*********************************************************************
*
*   HEADER NAME:
*       FileListWidget.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QtWidgets>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>

class FileListWidget : public QWidget
{
    Q_OBJECT

public:

enum LIST_TYPE
{
    FILE_LIST = 0,
    RESULT_LIST = 1
};

//----------------------------------------------------------------
// Functions
//----------------------------------------------------------------
public:
    FileListWidget
        (
        QWidget *widget
        );

    void initListType
        (
        LIST_TYPE aType
        );

    QTreeWidgetItem *getCurrentItem();

    QTreeWidget *getTree();

    void addSubDirectory
        (
        QString aPath
        );

    void addProjectDirectory
        (
        QString aPath
        );

    void delAll();

public slots:
    void delFile();

    void delFilePermanent();

    void addDirectory
        (
        QString path
        );

    void clickedEvent
        (
        QTreeWidgetItem *aItem,
        int aNumber
        );

    void doubleClickedEvent
        (
        QTreeWidgetItem *aItem,
        int aNumber
        );

    void showContextMenu(const QPoint &pos);
signals:
    void itemClicked
        (
        QTreeWidgetItem *aItem,
        int aNumber
        );

    void getFileFullPathName
        (
        QString fileName
        );

    void getFileName
        (
        QStringList fileName
        );

private:
    LIST_TYPE mType;
    QTreeWidget *mTree;
    QTreeWidgetItem *mRoot;
    QFileInfoList allfile( QTreeWidgetItem *aRoot, QString aPath );
    void DeleteItem(QTreeWidgetItem *item);
};

#endif // FILELISTWIDGET_H
