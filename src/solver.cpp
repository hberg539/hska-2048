#include "solver.h"

Solver::Solver()
{
}

Solver::Solver(int lastDirection)
{
    lastDirection=0;
}

Solver::Direction Solver::getDirection(int lastDirection)
{
    switch(lastDirection)
    {
    case 0:
        return Direction::RIGHT;
    case 1:
        return Direction::DOWN;
    default:;
    }
}

int Solver::getlastDirection()
{
    printf("return lastdirc = %d\n",this->lastDirection);
    return this->lastDirection;
}

void Solver::setlastDirection(int lastDirection)
{
    printf("lastDirection=%d\n",lastDirection);
    this->lastDirection=lastDirection;
    printf("thisdirc=%d\n",this->lastDirection);
}

Solver::Direction Solver::getBestDirection(const T_BOARD & board, unsigned int runs)
{
    // Run every N-times in every direction
    unsigned int scoreUp    = randomRun(board, Direction::UP, runs);
    unsigned int scoreRight = randomRun(board, Direction::RIGHT, runs);
    unsigned int scoreLeft  = randomRun(board, Direction::LEFT, runs);
    unsigned int scoreDown  = randomRun(board, Direction::DOWN, runs);

    unsigned int maxScore = std::max(scoreUp, std::max(scoreRight, std::max(scoreLeft, scoreDown)));

    if (maxScore == scoreUp)    return Direction::UP;
    if (maxScore == scoreRight) return Direction::RIGHT;
    if (maxScore == scoreLeft)  return Direction::LEFT;
    if (maxScore == scoreDown)  return Direction::DOWN;

    return Direction::DOWN;
}

unsigned int Solver::randomRun(const T_BOARD & board, Direction direction, unsigned int runs)
{
    unsigned int score_avg = 0;

    for (unsigned int i = 0; i < runs; i++)
    {
        score_avg += randomRun(board, direction);
    }

    return score_avg / runs;
}

unsigned int Solver::randomRun(const T_BOARD & board, Direction direction)
{
    // Make copy
    T_BOARD tmpboard = board;

    // Move possible?
    if (!isMovePossible(tmpboard, direction))
    {
        return 0;
    }

    // Move in direction
    moveBoard(tmpboard, direction);

    // Add random tile
    addRandomTile(tmpboard);

    // Run the game till the end
    unsigned int randomMove = 0;

    unsigned int i = 0;
    while (true)
    {
        // Break when no move is possible
        if (!isMovePossible(tmpboard)) break;

        // Or maximum of games played is reached
        if (i > 500) break;

        // Do a random move
        randomMove = rand() % (3 + 1);

        if (randomMove == 0) moveBoard(tmpboard, Direction::RIGHT);
        if (randomMove == 1) moveBoard(tmpboard, Direction::DOWN);
        if (randomMove == 2) moveBoard(tmpboard, Direction::LEFT);
        if (randomMove == 3) moveBoard(tmpboard, Direction::UP);

        // Add random tile
        addRandomTile(tmpboard);

        i++;
    }

    // return the points made
    return getPoints(tmpboard);
}

bool Solver::compareTiles(const T_BOARD & board)
{
    printf("Tile=%d\n",board[board.size()-1][board.size()-1]);
    if((board[board.size()-1][board.size()-2]==board[board.size()-2][board.size()-1]
       && board[board.size()-1][board.size()-1]>=board[board.size()-1][board.size()-2])
       || (board[board.size()-2][board.size()-3]==board[board.size()-3][board.size()-2]
           && board[board.size()-2][board.size()-2]>=board[board.size()-2][board.size()-3]))
        return true;
    else
        return false;

}

bool Solver::compareNumberTiles(const T_BOARD &board)
{
    unsigned int i=0,k=0,l=0,j=0;

    printf("board isze = %d\n",board.size());
    for(int a=0;a<board.size();a++)
    {
    if(board[board.size()-2][a]!=NULL)
        i++;
    if(board[board.size()-1][a]!=NULL)
        j++;
    if(board[board.size()-3][a]!=NULL)
        k++;
    }
    printf("i=%d j=%d\n",i,j);
    if(j==board.size())
    {
        if(i==(j-1))
            return true;
        else if(i==j==board.size() && k-1==(board.size()-1))
            return true;
    }
    else
        return false;
}

void Solver::addRandomTile(T_BOARD & board)
{
    // Get free positions
    std::vector<T_CORD> free_positions = getFreePositions(board);

    // Freie Position verfuegbar
    if (free_positions.size() > 0)
    {
        // Mische die Positionen zufaellig
        //std::random_shuffle(free_positions.begin(), free_positions.end());

        // Random index
        unsigned int index = std::rand() % free_positions.size();

        // Add to board
        board[free_positions[index].first][free_positions[index].second] = rand() % 100 >= 90 ? 4 : 2;
    }
}

std::vector<T_CORD> Solver::getFreePositions(const T_BOARD &board)
{
    std::vector<T_CORD> free_positions;

    // Find free positions
    for (unsigned i = 0; i < board.size(); i++)
    {
        for (unsigned j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                free_positions.push_back(std::make_pair(i, j));
            }
        }
    }

    return free_positions;
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
    if (isMovePossible(board, Direction::UP))    return true;
    if (isMovePossible(board, Direction::RIGHT)) return true;
    if (isMovePossible(board, Direction::DOWN))  return true;
    if (isMovePossible(board, Direction::LEFT))  return true;

    return false;
}

bool Solver::isRightDownPossible(const T_BOARD & board)
{
    if (isMovePossible(board, Direction::RIGHT)) return true;
    if (isMovePossible(board, Direction::DOWN))  return true;


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
    unsigned int dimension = static_cast<unsigned int>(board.size());

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
    unsigned int dimension = static_cast<unsigned int>(board.size());

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
    unsigned int dimension = static_cast<unsigned int>(board.size());

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
    unsigned int dimension = static_cast<unsigned int>(board.size());

//    T_BOARD board_new(dimension, std::vector<int>(dimension, 0));

//    // Faster version of rotate
//    for (unsigned int i = 0; i < board.size(); i++)
//    {
//        for (unsigned int j = 0; j < board.size(); j++)
//        {
//            board_new[i][j] = board[board.size() - j - 1][i];
//        }
//    }

//    board = board_new;

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
