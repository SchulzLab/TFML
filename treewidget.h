#ifndef TREEWIDGET_H
#define TREEWIDGET_H
#include <QtWidgets>
class TreeWidget : public QWidget
{
public:
    TreeWidget();

private:
    QTreeWidget *tree;
    QFileInfoList allfile(QTreeWidgetItem *root, QString path);
};

#endif // TREEWIDGET_H
