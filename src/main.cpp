#include "mainwindow.h"
#include <QApplication>

#include "definitions.h"
#include "core/board.h"
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
//    std::cout << "Running 2048 demo..." << std::endl;

//    // Command line demo
//    Board board(4);
//    QTextStream s(stdin);
//    QString value;

//    while (value != "q")
//    {
//        if (value == "l") board.move(Board::Direction::LEFT);
//        if (value == "r") board.move(Board::Direction::RIGHT);
//        if (value == "u") board.move(Board::Direction::UP);
//        if (value == "d") board.move(Board::Direction::DOWN);
//        if (value == "n") board.addRandomTile();
//        board.printBoard();

//        value = s.readLine();
//    }
//    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
