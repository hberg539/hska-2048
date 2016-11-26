#include "mainwindow.h"
#include <QApplication>

#include "definitions.h"
#include "core/game.h"
#include <iostream>
#include <QTextStream>

#include "solver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
