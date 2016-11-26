#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

typedef std::vector<std::vector<int> > T_BOARD;

class Solver
{
public:
    // Richtung
    enum class Direction { LEFT, RIGHT, UP, DOWN };

    Solver();

    // Test if any move is possible
    bool isMovePossible(const T_BOARD & board);
    bool isMovePossible(const T_BOARD &board, Direction direction);

    // Test Direction
    unsigned int evaluateMove(const T_BOARD &board, Direction direction);

    // Return points
    unsigned int getPoints(T_BOARD & board);

    // Move Board in Direction
    // Returns points made
    unsigned int moveBoard(T_BOARD & board, Direction direction);

    // Print Board
    void printBoard(const T_BOARD & board);

private:
    // Move Single Tile
    unsigned int moveSingle(T_BOARD & board, unsigned int pos_i, unsigned int pos_j, T_BOARD & flagsUpgraded);

    // Rotate Board
    void rotateBoard(T_BOARD & board);

};

#endif // SOLVER_H
