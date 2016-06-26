/*********************************************************************
*
*   MODULE NAME:
*       main.cpp
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
    window.showMaximized();

    return app.exec();
}
