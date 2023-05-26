/**
 * \file main.cpp
 * \author Théo Coufleaux
 * \version 1.1
 * \date 5 Mai 2023
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

