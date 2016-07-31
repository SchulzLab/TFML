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
    FileListWidget
        (
        QWidget *widget
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

public slots:
    void delFile();

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
    QTreeWidget *mTree;
    QTreeWidgetItem *mRoot;
    QFileInfoList allfile( QTreeWidgetItem *aRoot, QString aPath );
};

#endif // FILELISTWIDGET_H
