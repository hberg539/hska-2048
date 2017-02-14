#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

typedef std::vector<std::vector<int> > T_BOARD;
typedef std::pair<unsigned int, unsigned int> T_CORD;

class Solver
{
public:
    // Richtung
    enum class Direction { LEFT, RIGHT, UP, DOWN };

    Solver();
    Solver(int lastDirection);

    Direction getDirection(int direction);

    int getlastDirection();

    void setlastDirection(int a);

    // Get best direction
    Direction getBestDirection(const T_BOARD & board, unsigned int runs);

    // Add Random Tile
    void addRandomTile(T_BOARD &board);

    // Random run
    unsigned int randomRun(const T_BOARD & board, Direction direction);
    unsigned int randomRun(const T_BOARD & board, Direction direction, unsigned int runs);

    // Get all free positions
    std::vector<T_CORD> getFreePositions(const T_BOARD &board);

    // Check if Tiles with same Value are above each other
    bool mergevertical(const T_BOARD &board);

    // Check if Tiles in a row can be merge
    bool checkRowMerge(const T_BOARD &board);

    // Test if any move is possible
    bool isMovePossible(const T_BOARD &board);
    bool isMovePossible(const T_BOARD &board, Direction direction);
    bool isRightDownPossible(const T_BOARD &board);

    //
    bool compareNumberTiles(const T_BOARD &board,int mode);
    // Compare two diagonal tiles
    bool compareDiagonalTiles(const T_BOARD &board);

    // Test Direction
    unsigned int evaluateMove(const T_BOARD &board, Direction direction);

    // Return points
    unsigned int getPoints(T_BOARD &board);

    // Move Board in Direction
    // Returns points made
    unsigned int moveBoard(T_BOARD &board, Direction direction);

    // Print Board
    void printBoard(const T_BOARD &board);

private:
    // Move Single Tile
    unsigned int moveSingle(T_BOARD & board, unsigned int pos_i, unsigned int pos_j, T_BOARD & flagsUpgraded);

    // Rotate Board
    void rotateBoard(T_BOARD & board);

    int lastDirection;

};

#endif // SOLVER_H
