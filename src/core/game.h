#ifndef GAME_H
#define GAME_H

#include "core/board.h"
#include <iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

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

    //Lexikal Analyser
    bool lexikal(FILE *inf, tyyval *yyval);

private:

    // Board-Instanz
    Board * m_board;

    // Spielstatus
    State m_state;
};

#endif // GAME_H
