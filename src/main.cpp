#include "mainwindow.h"
#include <QApplication>

#include "definitions.h"
#include "core/board.h"
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    std::cout << "Running 2048 demo..." << std::endl;

    // Command line demo
    Game game(4);
    QTextStream s(stdin);
    QString value;

    while (value != "q")
    {
        if (value == "l") game.handleMove(Board::Direction::LEFT);
        if (value == "r") game.handleMove(Board::Direction::RIGHT);
        if (value == "u") game.handleMove(Board::Direction::UP);
        if (value == "d") game.handleMove(Board::Direction::DOWN);
        game.debugPrint();

        value = s.readLine();
    }
    return 0;

//        if (value == "d") board.move(Board::Direction::DOWN);
//        if (value == "n") board.addRandomTile();
//        board.printBoard();

//        value = s.readLine();
//    }
//    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    QKeyEvent *k;
    w.show();

    return a.exec();
    while(1)
    {

    w.setLable(); //lesen von keyboard
    }
}
