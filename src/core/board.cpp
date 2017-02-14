#include "core/board.h"

#include <iostream>
#include <algorithm>

/**
 * @brief Constructor for Board
 * @param dimension Size of board (e.g. 4 for 4x4)
 */
Board::Board(int dimension)
    : m_dimension(dimension)
{
    // Beim ersten Aufruf der Klasse (Konstruktor)
    // muss m_board mit der richtigen Dimension
    // initialisiert werden
    updateDimension(dimension);

    // Initialisiere Spielbrett
    clear();
}

/**
 * @brief Copy constructor for board that copies the m_board member.
 * @param ref
 */
Board::Board(const Board &ref)
{
    // Initilisiere Dimension
    updateDimension(ref.m_dimension);

    // Kopiere Tiles
    for (unsigned int i = 0; i < ref.m_dimension; i++)
    {
        for (unsigned int j = 0; j < ref.m_dimension; j++)
        {
            if (ref.m_board[i][j] == NULL)
            {
                m_board[i][j] = NULL;
            }
            else
            {
                m_board[i][j] = new Tile(*(ref.m_board[i][j]));
            }
        }
    }
}

/**
 * @brief Returns the board as int vector
 * @return int vector
 */
std::vector<std::vector<int> > Board::getBoardAsInt(void)
{
    std::vector<std::vector<int> > boardInt(m_dimension, std::vector<int>(m_dimension));

    for (unsigned int i = 0; i < m_dimension; i++)
    {
        for (unsigned int j = 0; j < m_dimension; j++)
        {
            if (m_board[i][j] == NULL)
            {
                boardInt[i][j] = 0;
            }
            else
            {
                boardInt[i][j] = m_board[i][j]->getValue();
            }
        }
    }

    return boardInt;
}

/**
 * @brief Apply a move direction to the board
 * @param dir Direction for the tiles to move
 * @return True when any tiles has been moved, otherwise False
 */
bool Board::move(Direction dir)
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

    return (move_cnt > 0) ? true : false;
}

/**
 * @brief Set value of a tile
 * @param i coordinate i
 * @param j coordinate j
 * @param value Tile value
 */
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

/**
 * @brief Test if any tile can be moved in the board
 * @return True when a tile can be moved, otherwise False
 */
bool Board::isAnotherMovePossible(void)
{
    // Aktuelles Spielbrett kopieren
    Board cur_board(*this);

    // Alle moeglichen Richtungen ausprobieren
    bool move_possible = false;    
    if (cur_board.move(Direction::UP))    move_possible = true;
    if (cur_board.move(Direction::RIGHT)) move_possible = true;
    if (cur_board.move(Direction::DOWN))  move_possible = true;
    if (cur_board.move(Direction::LEFT))  move_possible = true;

    return move_possible;
}

/**
 * @brief Main method for calculation moves and collisions with other tiles
 * @param pos_i coordinate i
 * @param pos_j coordinate j
 * @return True, when a move was done, otherwise False
 *
 * In this method a tile with given coordinates (i,j)
 * starts to "fall" to the ground. Any collisions (and merges) are
 * handled here.
 */
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

/**
 * @brief Rotate the whole board 90° clockwise
 */
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

/**
 * @brief Add a new random tile to the board.
 *
 * Probability for 2: 90%
 * Probability for 4: 10%
 */
void Board::addRandomTile(void)
{
    T_CORD new_pos = findFreePosition();

    // Nur hinzufuegen wenn der Rueckgabewert gueltig ist
    // -1 entspricht keiner freien Position
    if (new_pos.first >= 0 && new_pos.second >= 0)
    {
        m_board[new_pos.first][new_pos.second] = new Tile(rand() % 100 >= 90 ? 4 : 2);
    }
}

/**
 * @brief Clear the board of all tiles
 */
void Board::clear()
{
    // Setzte NULL als default
    for (unsigned i = 0; i < m_dimension; i++)
    {
        for (unsigned j = 0; j < m_dimension; j++)
        {
            m_board[i][j] = NULL;
        }
    }
}


/**
 * @brief Update dimension of the board
 * @param dimension Dimension of board (e.g. 4 for 4x4)
 */
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

/**
 * @brief Find a coordinate in the board without any tile.
 * @return coordinates (i,j)
 */
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

    // Keine freien Position mehr verfuegbar
    if (free_positions.size() == 0)
    {
        return std::make_pair(-1, -1);
    }
    else
    {
        return free_positions[0];
    }
}
