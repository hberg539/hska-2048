#include "core/Board.h"

#include <iostream>
#include <algorithm>

// Konstruktor
Board::Board(int dimension)
    : m_dimension(dimension)
{
    // Beim ersten Aufruf der Klasse (Konstruktor)
    // muss m_board mit der richtigen Dimension
    // initialisiert werden
    updateDimension(dimension);

    // Initialisiere Spielbrett
    init();
}

// Bewege das Spielbrett
void Board::move(Direction dir)
{
    // Rotiere Spielfeld in eine einheitliche Richtung
    // -> nach "UNTEN" (Schwerkraft)
    // Dadurch "Kollisionslogik" nur für eine Richtung notwendig
    switch (dir)
    {
    case Direction::RIGHT: rotate(); break;
    case Direction::UP:    rotate(); rotate(); break;
    case Direction::LEFT:  rotate(); rotate(); rotate(); break;
    }

    // Jedes Tile "faellt" nun nach unten,
    // beginnend von links unten
    unsigned int move_cnt = 0;

    for (unsigned int i = m_dimension; i > 0; i--)
    {
        for (unsigned int j = 0; j < m_dimension; j++)
        {
            if (moveTile(i - 1, j)) move_cnt++;
        }
    }

    // Rotiere Spielfeld zurueck
    switch (dir)
    {
    case Direction::RIGHT: rotate(); rotate(); rotate(); break;
    case Direction::UP:    rotate(); rotate(); break;
    case Direction::LEFT:  rotate(); break;
    }

    // Setze Upgraded-Flags zurueck
    for (unsigned int i = 0; i < m_dimension; i++)
    {
        for (unsigned int j = 0; j < m_dimension; j++)
        {
            if (m_board[i][j] != NULL)
            {
                m_board[i][j]->resetFlagUpgraded();
            }
        }
    }

    // Ein neues Tile soll erscheinen,
    // sofern eine Bewegung passiert ist
    if (move_cnt > 0)
    {
        addRandomTile();
    }
}

// Setze Tile
void Board::setTile(unsigned int i, unsigned int j, int value)
{
    if (m_board[i][j] == NULL)
    {
        m_board[i][j] = new Tile(value);
    }
    else
    {
        m_board[i][j]->updateValue(value);
    }
}

// Bewege ein einzelnes Tile
// Gibt true zurueck, wenn eine Bewegung ausgefuehrt wurde
bool Board::moveTile(unsigned int pos_i, unsigned int pos_j)
{
    // Ueberspringe leeres Tile
    if (m_board[pos_i][pos_j] == NULL)
    { return false; }

    Tile * cur_tile = getTile(pos_i, pos_j);
    Tile * next_tile;

    // Tile bereits am Boden?
    if (pos_i == m_dimension - 1)
    {
        return false;
    }

    // Bewege Tile nach unten
    bool collision = false;
    unsigned int i;

    for (i = pos_i; i < m_dimension - 1; i++)
    {
        // Kollision mit naechstem Tile
        if (m_board[i + 1][pos_j] != NULL)
        {
            next_tile = m_board[i + 1][pos_j];
            collision = true;

            // Tile bereits upgraded?
            // Dann Tile bleibt das Tile an dieser Stelle,
            // kein Merge!
            if (next_tile->getFlagUpgraded())
            {
                // Verschiebe Tile an die aktuelle Position
                m_board[i][pos_j]     = m_board[pos_i][pos_j];
                m_board[pos_i][pos_j] = NULL;
                return true;
            }

            // Kollision mit einem Tile gleichen Wertes
            if (next_tile->getValue() == cur_tile->getValue())
            {
                // Erhoehe Wert von next_tile, entferne cur_tile
                next_tile->upgrade();
                delete m_board[pos_i][pos_j];
                m_board[pos_i][pos_j] = NULL;
                return true;
            }

            // Kollision mit einem Tile anderen Wertes
            if (next_tile->getValue() != cur_tile->getValue())
            {
                // Verschiebe Tile an die aktuelle Position (vor der Kollsion),
                // sofern sich die Position vom Tile veraendert
                if (i != pos_i)
                {
                    m_board[i][pos_j]     = m_board[pos_i][pos_j];
                    m_board[pos_i][pos_j] = NULL;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    // Keine Kollision aufgetreten
    if (collision == false)
    {
        // Verschiebe Tile an die unterste Position
        m_board[m_dimension - 1][pos_j] = m_board[pos_i][pos_j];
        m_board[pos_i][pos_j]           = NULL;
        return true;
    }

    return false;
}

// Rotiere Spielbrett (in Richtung Uhrzeigersinn)
void Board::rotate()
{
    // Transpose the matrix
    for (unsigned int i = 0; i < m_dimension; i++ ) {
        for (unsigned int j = i + 1; j < m_dimension; j++ ) {
            void * tmp_ptr = static_cast<void *>(m_board[i][j]);
            m_board[i][j] = m_board[j][i];
            m_board[j][i] = static_cast<Tile *>(tmp_ptr);
        }
    }

    // Swap the columns
    for (unsigned int i = 0; i < m_dimension; i++ ) {
        for (unsigned int j = 0; j < m_dimension/2; j++ ) {
            void * tmp_ptr = static_cast<void *>(m_board[i][j]);
            m_board[i][j] = m_board[i][m_dimension-1-j];
            m_board[i][m_dimension-1-j] = static_cast<Tile *>(tmp_ptr);
        }
    }
}

// Neues zufaelliges Tile hinzufuegen
void Board::addRandomTile(void)
{
    T_CORD new_pos = findFreePosition();
    m_board[new_pos.first][new_pos.second] = new Tile(2);
}

// Spielbrett initialisieren
void Board::init()
{
    // Setzte NULL als default
    for (unsigned i = 0; i < m_dimension; i++)
    {
        for (unsigned j = 0; j < m_dimension; j++)
        {
            m_board[i][j] = NULL;
        }
    }

    // Setze 2 neue Tiles an zufaelliger Position
    addRandomTile();
    addRandomTile();
}

// Dimension aktualisieren
void Board::updateDimension(const unsigned int dimension)
{
    m_dimension = dimension;

    // Setze Dimension in Y-Richtung
    m_board.resize(m_dimension);

    // Setze Dimension in X-Richtung (für jede Y-Reihe)
    for (unsigned int i = 0; i < m_dimension; i++)
    {
        m_board[i].resize(m_dimension);
    }
}

// Gibt ein freie Position als Pair zurueck (i,j)
T_CORD Board::findFreePosition(void)
{
    std::vector<T_CORD> free_positions;

    // Gehe ueber jede Zelle und pruefe, ob die Zelle leer ist (== NULL)
    for (unsigned int i = 0; i < m_dimension; i++)
    {
        for (unsigned int j = 0; j < m_dimension; j++)
        {
            if (m_board[i][j] == NULL)
            {
                free_positions.push_back(std::make_pair(i, j));
            }
        }
    }

    // Mische die Positionen zufaellig
    std::random_shuffle(free_positions.begin(), free_positions.end());

    // Lost?
    if (free_positions.size() == 0)
    {
        // ???
    }
    else
    {
        return free_positions[0];
    }
}

// Only for debug
void Board::printBoard(void)
{
    std::cout << "Current board state:" << std::endl;

    for (unsigned int i = 0; i < m_dimension; i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;

    for (unsigned int i = 0; i < m_dimension; i++)
    {
        for (unsigned int j = 0; j < m_dimension; j++)
        {
            if (getTile(i, j) != NULL)
            {
                std::printf("|%4d", getTile(i, j)->getValue());
            }
            else
            {
                std::cout << "|    ";
            }

        }
        std::cout << "|" << std::endl;
    }

    for (unsigned int i = 0; i < m_dimension; i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;
}
