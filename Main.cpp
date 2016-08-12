/*********************************************************************
*
*   MODULE NAME:
*       Main.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setGeometry( QApplication::desktop ()->availableGeometry() );
    window.showMaximized();

    return app.exec();
}
