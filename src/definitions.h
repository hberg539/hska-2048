#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <vector>

typedef std::pair<unsigned int, unsigned int> T_CORD;

// Enum fuer Algorithmus
enum class Algorithm { ALGO_RANDOM, ALGO_LEFT_RIGHT, ALGO_PURE_MONTE_CARLO };

// Enum fuer Command
enum class Command { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, IDLE };

#endif // DEFINITIONS_H
