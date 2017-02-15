/**
 * @file worker.h
 * @brief Class which contains algorithms for solving the game.
 *        Is run in QThread.
 */

#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QKeyEvent>
#include <QTime>
#include <iostream>
#include <ctime>
#include "core/game.h"
#include "solver.h"
#include "definitions.h"
#include <intrin.h>

/**
 * @brief Worker class, contains algorithms for solving the game.
 */
class Worker : public QThread
{
    Q_OBJECT

public:
    Worker();

    // Start / Stopped Variable
    bool m_enabled;

    // Only one time
    bool m_single;

    // Set Interval
    void setInterval(unsigned int interval)
    { m_interval = interval; }

    // Get Interval
    unsigned int getInterval(void)
    { return m_interval; }

    // Set Algorithm
    void setAlgorithm(Algorithm algorithm)
    { m_algorithm_selected = algorithm; }

    // Setze Game Instanz
    void setGame(Game * game)
    { m_game = game; }

private:
    void run();

    // Worker for Random
    Command workerRandom();

    // Worker for Pure Monte Carlo
    Command workerPureMonteCarlo();

    // Worker for Right Down
    Command workerRightDown(Solver &solva);

    // Algorithm selected
    Algorithm m_algorithm_selected;

    // Intervall
    unsigned int m_interval;

    // Number of CPU cycles
    uint64_t m_num_cycles;

    // Number of turns
    uint64_t m_num_turns;

    // Game Instanz
    Game * m_game;

    // Game won?
    bool m_game_won;

signals:
    void sendKeyEvent(QKeyEvent * event);
};

#endif // WORKER_H
