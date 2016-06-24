#include "treewidget.h"

TreeWidget::TreeWidget()
{
    tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString("Root")));
    allfile(root, "./");
    QTreeWidgetItem *root1 = new QTreeWidgetItem(tree, QStringList(QString("Root1")));
    allfile(root1, "../");
    //QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    //root->addChild(leaf);
    //QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    //leaf2->setCheckState(0, Qt::Checked);
    //root->addChild(leaf2);
    QList<QTreeWidgetItem *> rootList;
    QList<QTreeWidgetItem *> rootList1;
    rootList.append(root);
    rootList1.append(root1);
            //<< root << root1;
    //tree->insertTopLevelItems(0, rootList);
    tree->insertTopLevelItems(1, rootList1);
}

QFileInfoList TreeWidget::allfile(QTreeWidgetItem *root, QString path)         //参数为主函数中添加的item和路径名
{

    /*添加path路径文件*/
    QDir dir(path);          //遍历各级子目录
    QDir dir_file(path);    //遍历子目录中所有文件
    dir_file.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);        //获取当前所有文件
    //dir_file.setNameFilters(filters);
    dir_file.setSorting(QDir::Name);
    QFileInfoList list_file = dir_file.entryInfoList();
    for (int i = 0; i < list_file.size(); ++i) {       //将当前目录中所有文件添加到treewidget中
        QFileInfo fileInfo = list_file.at(i);
        QString name2=fileInfo.fileName();
        QString namesuffix = fileInfo.suffix();
        QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<<name2);
        //child->setIcon(0, QIcon("./Resources/images/link.png"));
        //child->setIcon(0, fileExtensionIcon(namesuffix));
        child->setCheckState(1, Qt::Checked);
        root->addChild(child);
    }


    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);   //获取当前所有目录

    for(int i = 0; i != folder_list.size(); i++)         //自动递归添加各目录到上一级目录
    {

             QString namepath = folder_list.at(i).absoluteFilePath();    //获取路径
             QFileInfo folderinfo= folder_list.at(i);
             QString name=folderinfo.fileName();      //获取目录名
             QTreeWidgetItem* childroot = new QTreeWidgetItem(QStringList()<<name);
             childroot->setIcon(0, QIcon("./Resources/images/file.png"));
             childroot->setCheckState(1, Qt::Checked);
             root->addChild(childroot);              //将当前目录添加成path的子项
             QFileInfoList child_file_list = allfile(childroot,namepath);          //进行递归
             file_list.append(child_file_list);
             file_list.append(name);
     }
    return file_list;
}
