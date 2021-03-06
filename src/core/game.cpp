#include "core/game.h"
#include "core/cparser.h"

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include <stdlib.h>

/**
 * @brief Chhbonstructor for the game class.
 * @param dimension Dimension of the board (e.g. 4, 4x4).
 */
Game::Game(int dimension)
    : m_state   (Game::State::GAME_RUNNING)
{
    // Init Board
    m_board = new Board(dimension);

    // Reset Game
    resetGame(dimension);
}

/**
 * @brief Checks if a move is possible and applys the direction. Also adds a new random tile.
 * @param direction Direction to apply.
 * @return True, when a move was done, otherwhise False.
 */
bool Game::handleMove(Board::Direction direction)
{
    // Testen, ob ueberhaupt eine Bewegung moeglich ist
    if (!m_board->isAnotherMovePossible())
    {
        m_state = State::GAME_LOST;
        return false;
    }

    // Bewegung durchfuehren
    bool has_moved = m_board->move(direction);

    // Testen, ob ein Tile >= 2048 ist
    // -> dann ist das Spiel gewonnen
    if (isGameWon())
    {
        m_state = State::GAME_WON;
    }

    // Ein neues Tile soll erscheinen,
    // sofern eine Bewegung passiert ist
    if (has_moved)
    {
        m_board->addRandomTile();
    }

    return true;
}

/**
 * @brief Clears the board, reset the game state and adds random tiles.
 */
void Game::resetGame(void)
{
    // Clear board
    m_board->clear();

    // Reset state
    m_state = State::GAME_RUNNING;

    // Fuege erste Tiles hinzu
    m_board->addRandomTile();
    m_board->addRandomTile();
}

/**
 * @brief Resets the game like resetGame(void), but with dimension update.
 * @param dimension Dimension of the board (e.g. 4, 4x4)
 */
void Game::resetGame(int dimension)
{
    // Aendere dimension
    m_board->updateDimension(dimension);

    // Setze zurueck
    resetGame();
}

/**
 * @brief Checks if the game is won (one 2048 tile exists)
 * @return True / False
 */
bool Game::isGameWon(void)
{
    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                if (m_board->getTile(i, j)->getValue() >= 2048)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief Calculates the points for the game
 * @return Points
 *
 * Sums the value of all tiles in the board.
 */
unsigned int Game::getPoints(void)
{
    unsigned int points = 0;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                points += m_board->getTile(i, j)->getValue();
            }
        }
    }
    return points;
}

/**
 * @brief Debug output of board. Not used in production.
 */
void Game::debugPrint(void)
{
    std::cout << "Points: " << getPoints() << std::endl;
    std::cout << "Current board state:" << std::endl;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                std::printf("|%4d", m_board->getTile(i, j)->getValue());
            }
            else
            {
                std::cout << "|    ";
            }

        }
        std::cout << "|" << std::endl;
    }

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;
}

/**
 * @brief Load gamedata from file
 * @param filename
 * @param loadmsg Give the result of the load process (not) successful
 * @return
 */
bool Game::load(string filename, string &loadmsg)
{
    CParser filescanner;
    string temp;
    FILE *loadfile;
    int x, y, z, tok;


    loadfile = fopen(filename.c_str(), "r");

    if(loadfile==NULL){
        loadmsg = "Error: Fileloading not successful!";
        return false;
    }

    filescanner.InitParse(loadfile, stderr, stdout);

    //tok = filescanner.yyparse();                                            //Liest naechstes Zeichen ein und git Typ zurueck (Integer, Variable, ...)

    while((tok = filescanner.yyparse()) != 0) {

        if (tok == C_IDENTIFIER && filescanner.yylval.s == "size"){         //Erst kommt size Variable
            tok = filescanner.yyparse();
            if (tok == C_INTEGER1){                                         //Dann kommt eigentliche Groesse
                m_board->updateDimension(filescanner.yylval.i);            //Quadratisches Spielfeld
                m_board->clear();
            }
            else{
                loadmsg = "Error: Format Error";
                return false;
            }
        }
        else if (tok == C_IDENTIFIER && filescanner.yylval.s.at(0) == 'x'){
            temp = filescanner.yylval.s.substr(1);                              //Zahl hinter x
            x = atoi(temp.c_str()) ;                                            //String in Integer
        }
        else if (tok == C_IDENTIFIER && filescanner.yylval.s.at(0) == 'y'){
            temp = filescanner.yylval.s.substr(1);
            y = atoi(temp.c_str()) ;
        }
        else if (tok == C_IDENTIFIER && filescanner.yylval.s.at(0) == 'z'){
            temp = filescanner.yylval.s.substr(1);
            z = atoi(temp.c_str()) ;
            m_board->setTile(y, x, z);
        }

        //tok = filescanner.yyparse();        //Next
    }

    // Reset game state
    m_state = State::GAME_RUNNING;

    fclose(loadfile);

    loadmsg = "Loading successful!";
    return true;

}


