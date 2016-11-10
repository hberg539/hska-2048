#ifndef GAME_H
#define GAME_H

#include "core/board.h"
#include <iostream>

class Game
{
public:

    // Konstruktor
    Game(int dimension);

    // Behandle Bewegung
    bool handleMove(Board::Direction direction);

    // Gebe Spielstand zurueck
    unsigned int getPoints(void);

    // Gebe das Spielbrett zurueck
    Board * getBoard(void)
    { return m_board; }

    // Only debug
    void debugPrint(void);

private:
    Board * m_board;
};

#endif // GAME_H
