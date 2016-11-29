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

    // Algorithm selected
    Algorithm m_algorithm_selected;

    // Intervall
    unsigned int m_interval;

    // Game Instanz
    Game * m_game;

    // Game won?
    bool m_game_won;

signals:
    void sendKeyEvent(QKeyEvent * event);
};

#endif // WORKER_H
