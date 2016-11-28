#ifndef GAME_H
#define GAME_H

#include "core/board.h"
#include <iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

class Game
{
public:

    // Spielstatus
    enum class State { GAME_RUNNING, GAME_WON, GAME_LOST };

    // Konstruktor
    Game(int dimension);

    // Behandle Bewegung
    bool handleMove(Board::Direction direction);

    // Gebe Spielstand zurueck
    unsigned int getPoints(void);

    // Setze Spiel zurueck
    void resetGame(void);
    void resetGame(int dimension);

    // Gebe das Spielbrett zurueck
    Board * getBoard(void)
    { return m_board; }

    // Gebe Spielstatus zurueck
    State getState(void)
    { return m_state; }

    // Teste, ob Spiel gewonnen
    bool isGameWon(void);

    // Only debug
    void debugPrint(void);

    //Load Game
    bool load(string filename, string &loadmsg);

private:

    // Board-Instanz
    Board * m_board;

    // Spielstatus
    State m_state;
};

#endif // GAME_H
