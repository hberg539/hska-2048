#ifndef GAME_H
#define GAME_H

#include "core/Board.h"
#include <iostream>

class Game
{
public:

    // Konstruktor
    Game(int dimension);

    // Behandle Bewegung
    bool handleMove(Board::Direction direction);

    // Only debug
    void debugPrint(void);

private:
    Board * m_board;
};

#endif // GAME_H
