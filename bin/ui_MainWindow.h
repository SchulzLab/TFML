/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "FileListWidget.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *mTabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QMenuBar *mMenuBar;
    QToolBar *mMainToolBar;
    QStatusBar *statusBar;
    QDockWidget *mDockLeft;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    FileListWidget *mFileList;
    QDockWidget *mDockResult;
    QWidget *dockWidgetContents1;
    QHBoxLayout *horizontalLayout1;
    FileListWidget *mResultFileList;
    QDockWidget *mBottomDock;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout2;
    QTextEdit *mLogText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1080, 783);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, -1, 0);
        mTabWidget = new QTabWidget(centralWidget);
        mTabWidget->setObjectName(QStringLiteral("mTabWidget"));
        mTabWidget->setMinimumSize(QSize(561, 561));
        mTabWidget->setTabsClosable(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setReadOnly(true);

        verticalLayout_2->addWidget(textEdit);

        mTabWidget->addTab(tab, QString());

        verticalLayout->addWidget(mTabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mMenuBar = new QMenuBar(MainWindow);
        mMenuBar->setObjectName(QStringLiteral("mMenuBar"));
        mMenuBar->setGeometry(QRect(0, 0, 1080, 27));
        MainWindow->setMenuBar(mMenuBar);
        mMainToolBar = new QToolBar(MainWindow);
        mMainToolBar->setObjectName(QStringLiteral("mMainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mMainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mDockLeft = new QDockWidget(MainWindow);
        mDockLeft->setObjectName(QStringLiteral("mDockLeft"));
        mDockLeft->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mFileList = new FileListWidget(dockWidgetContents);
        mFileList->setObjectName(QStringLiteral("mFileList"));
        mFileList->setMouseTracking(false);

        horizontalLayout->addWidget(mFileList);

        mDockLeft->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), mDockLeft);
        mDockResult = new QDockWidget(MainWindow);
        mDockResult->setObjectName(QStringLiteral("mDockResult"));
        mDockResult->setMinimumSize(QSize(300, 40));
        mDockResult->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea);
        dockWidgetContents1 = new QWidget();
        dockWidgetContents1->setObjectName(QStringLiteral("dockWidgetContents1"));
        horizontalLayout1 = new QHBoxLayout(dockWidgetContents1);
        horizontalLayout1->setSpacing(6);
        horizontalLayout1->setContentsMargins(11, 11, 11, 11);
        horizontalLayout1->setObjectName(QStringLiteral("horizontalLayout1"));
        horizontalLayout1->setContentsMargins(0, 0, 0, 0);
        mResultFileList = new FileListWidget(dockWidgetContents1);
        mResultFileList->setObjectName(QStringLiteral("mResultFileList"));

        horizontalLayout1->addWidget(mResultFileList);

        mDockResult->setWidget(dockWidgetContents1);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), mDockResult);
        mBottomDock = new QDockWidget(MainWindow);
        mBottomDock->setObjectName(QStringLiteral("mBottomDock"));
        sizePolicy.setHeightForWidth(mBottomDock->sizePolicy().hasHeightForWidth());
        mBottomDock->setSizePolicy(sizePolicy);
        mBottomDock->setMinimumSize(QSize(500, 150));
        mBottomDock->setMaximumSize(QSize(524287, 524287));
        mBottomDock->setLayoutDirection(Qt::LeftToRight);
        mBottomDock->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        horizontalLayout2 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout2->setSpacing(0);
        horizontalLayout2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout2->setObjectName(QStringLiteral("horizontalLayout2"));
        horizontalLayout2->setContentsMargins(9, 0, 9, 0);
        mLogText = new QTextEdit(dockWidgetContents_2);
        mLogText->setObjectName(QStringLiteral("mLogText"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mLogText->sizePolicy().hasHeightForWidth());
        mLogText->setSizePolicy(sizePolicy1);
        mLogText->setMouseTracking(false);
        mLogText->setAutoFillBackground(true);

        horizontalLayout2->addWidget(mLogText);

        mBottomDock->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), mBottomDock);

        retranslateUi(MainWindow);

        mTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Start project:</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1. File-&gt;New/Load project.</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2. File-&gt;Load file/directory to add file.</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3. Tools-&gt;TEPIC t"
                        "o start analysis </p></body></html>", 0));
        mTabWidget->setTabText(mTabWidget->indexOf(tab), QApplication::translate("MainWindow", "Start", 0));
        mDockLeft->setWindowTitle(QApplication::translate("MainWindow", "FileList", 0));
        mDockResult->setWindowTitle(QApplication::translate("MainWindow", "ResultList", 0));
        mBottomDock->setWindowTitle(QApplication::translate("MainWindow", "Console Output", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
