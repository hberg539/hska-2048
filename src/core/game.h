/**
 * @file core/game.h
 * @brief Main game class for the game 2048.
 *        Contains one board (core/board.h).
 */

#ifndef GAME_H
#define GAME_H

#define C_STRING1  3
#define C_IDENTIFIER  4
#define C_INTEGER1  5

#include "core/board.h"
#include "core/cparser.h"
#include <iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

/**
 * @brief Game class, manages the board, points, game state and loads savegames.
 */
class Game
{
public:

    // Spielstatus
    enum class State { GAME_RUNNING, GAME_WON, GAME_LOST };

    // Datentypen fuer lexikal
    enum lexstate{L_START, L_INT, L_IDENT, L_OPERATOR, L_VARIABLE, L_ADRESS, L_FILEEND};

    // Struct fuer lexikal
    struct tyyval{
        string s, si;       //s für Text, si für Zahlen die später zu einem Integer gewandelt werden
        int i;              //i für ausgelesene Zahlen
        lexstate type;     //type gibt um welchen Datentyp es sich handelt
    };

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
