#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"
#include "core/tile.h"
#include <vector>
#include <algorithm>
#include <iterator>

/**
 * @brief Board Klasse
 *
 * Die Spielbrett-Klasse verwaltet alle Kasten (Tiles).
 */

class Board
{
public:

    // Richtung
    enum Direction { LEFT, RIGHT, UP, DOWN };

    // Konstruktor
    Board(int dimension);

    // Kopier-Konstruktor
    Board(const Board& ref);

    // Aktualisiere Dimension vom Spielbrett
    void updateDimension(const unsigned int dimension);

    // Gebe aktuelle Dimension zurück
    unsigned int getDimension(void)
    { return m_dimension; }

    // Gebe Tile zurueck
    Tile * getTile(const unsigned int i, const unsigned int j)
    { return m_board[i][j]; }

    // Setze Tile
    void setTile(unsigned int i, unsigned int j, int value);

    // Finde eine freie Position
    T_CORD findFreePosition(void);

    // Neues Tile hinzufuegen
    void addRandomTile(void);

    // Bewege das Spielbrett
    bool move(Direction dir);

    // Bewege einzelne Tiles
    bool moveTile(unsigned int i, unsigned int j);

    // Rotiere Spielbrett
    void rotate();

    // Testen ob ein weiterer Spielzug moeglich ist
    bool isAnotherMovePossible(void);

private:

    // Member Dimension
    unsigned int m_dimension;

    // Member aller Tiles (NxN Matrix)
    //
    // Beispiel (dim=2)
    // -----
    // |1|2|
    // |3|4|
    // -----
    // Zugriff:
    //    1 -> m_board[0][0]
    //    2 -> m_board[0][1]
    //    3 -> m_board[1][0]
    //    4 -> m_board[1][1]
    std::vector<std::vector<Tile *>> m_board;


    // Initialisiere Board
    void init(void);
};

#endif // BOARD_H
