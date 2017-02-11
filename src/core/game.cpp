#include "core/game.h"

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include <stdlib.h>

Game::Game(int dimension)
    : m_state   (Game::State::GAME_RUNNING)
{
    // Init Board
    m_board = new Board(dimension);

    // Reset Game
    resetGame(dimension);
}


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

void Game::resetGame(int dimension)
{
    // Aendere dimension
    m_board->updateDimension(dimension);

    // Setze zurueck
    resetGame();
}

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

// Gebe Punktestand zurueck
// Original: Punkte entspricht den Wert aller Upgrades
// Unsere Version: Einfach nur die Werte aller Tiles
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

bool Game::load(string filename, string &loadmsg)
{
    tyyval result;
    FILE *loadfile;
    int x, y;

    loadfile = fopen(filename.c_str(), "r");

    if(loadfile==NULL){
        loadmsg = "Error: Fileloading not sucesfull!";
        return false;
    }

    do {
        lexikal(loadfile, &result);
        if (result.type == L_VARIABLE && result.s == "size"){
            lexikal(loadfile, &result);
            if (result.type == L_INT){
                m_board->updateDimension(result.i);            //Quadratisches Spielfeld
                m_board->clear();
            }
        }
        else if (result.type == L_ADRESS && result.s == "x"){
            x = result.i;
        }
        else if (result.type == L_ADRESS && result.s == "y"){
            y = result.i;
        }
        else if (result.type == L_VARIABLE && result.s == "z"){
            lexikal(loadfile, &result);
            if (result.type == L_INT){
                m_board->setTile(y, x, result.i);
            }
        }
    }
    while (result.type != L_FILEEND);

    fclose(loadfile);



//    ifstream infile (filename.c_str());
//    int MAX=80;
//    char buffer[MAX+1];
//    int x, y, z, found, xsize, ysize;

//    //Erste Zeile wird eingelesen und Spielfeld Groesse ausglesen

//    infile.getline(buffer, MAX);

//    found = string(buffer).find("x=") + 2;
//    if (isdigit(buffer[found]))
//    {
//        xsize = atoi (buffer + found);
//    }

//    found = string(buffer).find("y=") + 2;
//    if (isdigit(buffer[found]))
//    {
//        ysize = atoi (buffer + found);
//    }

//    m_board->updateDimension(xsize);            //Quadratisches Spielfeld
//    m_board->clear();


//    infile.getline(buffer, MAX);            //Zweite Zeile ueberspringen

//    //Es werden solange die Spielfelddaten eingelesen bis das Ende erreicht wurde

//    while (!infile.eof())
//    {
//        infile.getline(buffer, MAX);

//        found = string(buffer).find("x") + 1;

//        if (isdigit(buffer[found]))
//        {
//            x = atoi (buffer + found);      //String in Zahl umwandeln
//        }

//        found = string(buffer).find("y") + 1;
//        if (isdigit(buffer[found]))
//        {
//            y = atoi (buffer + found);
//        }

//        found = string(buffer).find("z=") + 2;
//        if (isdigit(buffer[found]))
//        {
//            z = atoi (buffer + found);
//        }

//        if ((x >= xsize) || (y >= xsize))
//        {
//            loadmsg = "Error: To much data!";
//            return false;
//        }
//        else
//        {
//            m_board->setTile(y, x, z);
//        }

//    }

    loadmsg = "Loading sucessfull!";
    return true;

}

bool Game::lexikal(FILE *inf, tyyval *yyval)
{
    int c = 0;
    lexstate s;
    s = L_START;

    while(c != EOF)
    {
        c = getc(inf);

        switch(s){
            case L_START:
                yyval->s = "";
                yyval->si = "";
                yyval->i = 0;
                if (isdigit(c)){
                    s = L_INT;
                    yyval->si.append (1, c);
                }
                else if (isalpha(c)){
                    s = L_IDENT;
                    yyval->s.append (1, c);
                }
            break;
            case L_INT:
                if (isdigit(c)){
                    s = L_INT;
                    yyval->si.append (1, c);
                }
                else{
                    //s = L_START;
                    ungetc(c, inf);
                    yyval->type = s;
                    yyval->i = atoi(yyval->si.c_str());
                    return (true);
                    //printf("Number: %d\n", yyval.i);
                }
                break;
            case L_IDENT:     //Hier wird geprueft, ob es sich um eine Adresse oder Variable handelt
                if (isdigit(c)){
                    s = L_ADRESS;
                    yyval->si.append (1, c);
                }
                else if (isalpha(c)){
                    s = L_VARIABLE;
                    yyval->s.append(1, c);
                }
                else if (c == 61){          //Fuer Variablen mit einem Buchstaben, 61= "="
                    //s = L_START;
                    yyval->type = L_VARIABLE;
                    return (true);
                    //printf("Variable: %s\n", yyval.s.c_str());
                }
                else{
                    printf("ERROR input\n");
                    s = L_START;
                }
                break;
            case L_ADRESS:
                if (isdigit(c)){
                    yyval->si.append (1, c);
                }
                else if(c == 44){
                    yyval->i = atoi(yyval->si.c_str());
                    yyval->type = s;
                    return (true);
                    //printf("Adress: %s%d\n", yyval.s.c_str(), yyval.i);
                    //s = L_START;
                }
                else{
                    printf("ERROR input\n");
                    s = L_START;
                }
                break;
            case L_VARIABLE:
                if (isalpha(c)){
                    yyval->s.append(1, c);
                }
                else if(c == 61){
                    yyval->type = s;
                    return (true);
                    //printf("Variable: %s\n", yyval.s.c_str());
                    //s = L_START;
                }
                else{
                    printf("ERROR input\n");
                    s = L_START;
                }
                break;
        }

    }

    yyval->type = L_FILEEND;
    return true;

}


