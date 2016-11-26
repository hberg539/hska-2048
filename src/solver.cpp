#include "solver.h"

Solver::Solver()
{

}

bool Solver::isMovePossible(const T_BOARD &board, Direction direction)
{
    // Copy of Board
    T_BOARD tmpboard = board;

    // Move
    moveBoard(tmpboard, direction);

    // Compare
    for (unsigned i = 0; i < board.size(); i++)
    {
        for (unsigned j = 0; j < board.size(); j++)
        {
            if (tmpboard[i][j] != board[i][j]) return true;
        }
    }

    return false;
}

// Test if any move is possible
bool Solver::isMovePossible(const T_BOARD & board)
{
    for (auto dir : std::vector<Direction>{Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT})
    {
        if (isMovePossible(board, dir)) return true;
    }

    return false;
}

unsigned int Solver::evaluateMove(const T_BOARD &board, Direction direction)
{
    // Copy of Board
    T_BOARD tmpboard = board;

    // Apply Direction and save points made
    return moveBoard(tmpboard, direction);
}


unsigned int Solver::getPoints(T_BOARD &board)
{
    unsigned int points = 0;
    unsigned int dimension = board.size();

    for (unsigned int i = 0; i < dimension; i++)
    {
        for (unsigned int j = 0; j < dimension; j++)
        {
            points += board[i][j];
        }
    }
    return points;
}

unsigned int Solver::moveSingle(T_BOARD & board, unsigned int pos_i, unsigned int pos_j, T_BOARD & flagsUpgraded)
{
    unsigned int dimension = board.size();

    // Ueberspringe leeres Tile
    if (board[pos_i][pos_j] == NULL)
    { return 0; }

    // Tile bereits am Boden?
    if (pos_i == dimension - 1)
    {
        return 0;
    }

    // Bewege Tile nach unten
    bool collision = false;
    unsigned int i;

    for (i = pos_i; i < dimension - 1; i++)
    {
        // Kollision mit naechstem Tile
        if (board[i + 1][pos_j] != 0)
        {
            //next_tile = board[i + 1][pos_j];
            collision = true;

            // Tile bereits upgraded?
            // Dann Tile bleibt das Tile an dieser Stelle,
            // kein Merge!
            if (flagsUpgraded[i + 1][pos_j])
            {
                // Verschiebe Tile an die aktuelle Position
                board[i][pos_j]     = board[pos_i][pos_j];
                board[pos_i][pos_j] = 0;
                return 0;
            }

            // Kollision mit einem Tile gleichen Wertes
            if (board[i + 1][pos_j] == board[pos_i][pos_j])
            {
                // Erhoehe Wert von next_tile, entferne cur_tile
                board[i + 1][pos_j] = board[i + 1][pos_j] * 2;
                board[pos_i][pos_j] = 0;
                flagsUpgraded[i + 1][pos_j] = 1;
                return board[i + 1][pos_j];
            }

            // Kollision mit einem Tile anderen Wertes
            if (board[i + 1][pos_j] != board[pos_i][pos_j])
            {
                // Verschiebe Tile an die aktuelle Position (vor der Kollsion),
                // sofern sich die Position vom Tile veraendert
                if (i != pos_i)
                {
                    board[i][pos_j]     = board[pos_i][pos_j];
                    board[pos_i][pos_j] = 0;
                }
                return 0;
            }
        }
    }

    // Keine Kollision aufgetreten
    if (collision == false)
    {
        // Verschiebe Tile an die unterste Position
        board[dimension - 1][pos_j] = board[pos_i][pos_j];
        board[pos_i][pos_j]           = 0;
        return 0;
    }

    return 0;
}

unsigned int Solver::moveBoard(T_BOARD &board, Direction direction)
{
    unsigned int dimension = board.size();

    // Points
    unsigned int points = 0;

    // Upgraded Flags
    T_BOARD flagsUpgraded;
    flagsUpgraded.resize(dimension, std::vector<int>(dimension, 0));

    // Rotiere Spielfeld in eine einheitliche Richtung
    // -> nach "UNTEN" (Schwerkraft)
    // Dadurch "Kollisionslogik" nur für eine Richtung notwendig
    switch (direction)
    {
    case Direction::RIGHT: rotateBoard(board); break;
    case Direction::UP:    rotateBoard(board); rotateBoard(board); break;
    case Direction::LEFT:  rotateBoard(board); rotateBoard(board); rotateBoard(board); break;
    }

    // Jedes Tile "faellt" nun nach unten,
    // beginnend von links unten
    unsigned int move_cnt = 0;

    for (unsigned int i = dimension; i > 0; i--)
    {
        for (unsigned int j = 0; j < dimension; j++)
        {
            points += moveSingle(board, i - 1, j, flagsUpgraded);
        }
    }

    // Rotiere Spielfeld zurueck
    switch (direction)
    {
    case Direction::RIGHT: rotateBoard(board); rotateBoard(board); rotateBoard(board); break;
    case Direction::UP:    rotateBoard(board); rotateBoard(board); break;
    case Direction::LEFT:  rotateBoard(board); break;
    }

    return points;
}

void Solver::rotateBoard(T_BOARD & board)
{
    unsigned int dimension = board.size();

    // Transpose the matrix
    for (unsigned int i = 0; i < dimension; i++ ) {
        for (unsigned int j = i + 1; j < dimension; j++ ) {
            unsigned int tmp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = tmp;
        }
    }

    // Swap the columns
    for (unsigned int i = 0; i < dimension; i++ ) {
        for (unsigned int j = 0; j < dimension/2; j++ ) {
            unsigned int tmp = board[i][j];
            board[i][j] = board[i][dimension-1-j];
            board[i][dimension-1-j] = tmp;
        }
    }
}

void Solver::printBoard(const T_BOARD & board)
{
    for (unsigned int row = 0; row < board.size(); row++)
    {
        for (unsigned int col = 0; col < board.size(); col++)
        {
            std::cout << "[" << board[row][col] << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
