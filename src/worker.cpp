#include "worker.h"

Worker::Worker() :
    m_enabled   (false),
    m_single    (false)
{
    srand(time(0));
}

void Worker::run()
{
    while (m_enabled)
    {
        // Start counter
        QTime update_start;
        update_start.start();

        // Command
        Command command = Command::IDLE;

        // Run Alogrithm
        switch (m_algorithm_selected)
        {
            case Algorithm::ALGO_RANDOM:
                command = workerRandom();
            break;

            case Algorithm::ALGO_PURE_MONTE_CARLO:
                command = workerPureMonteCarlo();
                break;
        }

        // Apply command
        switch (command)
        {
            case Command::MOVE_LEFT:
            {
                QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier, "");
                emit sendKeyEvent(event);
                break;
            }
            case Command::MOVE_RIGHT:
            {
                QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier, "");
                emit sendKeyEvent(event);
                break;
            }
            case Command::MOVE_UP:
            {
                QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, "");
                emit sendKeyEvent(event);
                break;
            }
            case Command::MOVE_DOWN:
            {
                QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier, "");
                emit sendKeyEvent(event);
                break;
            }
        }

        // Beende Solver wenn Spiel gewonnen
        if (m_game->getState() == Game::State::GAME_WON && m_game_won == false)
        {
            // Stoppe Worker
            m_enabled = false;

            // Set Flag
            m_game_won = true;
        }

        // Beende Solver wenn Spiel verloren
        if (m_game->getState() == Game::State::GAME_LOST)
        {
            // Stoppe Worker
            m_enabled = false;
        }

        // Single run
        if (m_single)
        {
            m_single = false;
            m_enabled = false;
            break;
        }

        // Time difference
        unsigned int update_ms = update_start.elapsed();

        if (update_ms > m_interval)
        {
            QThread::msleep(2);
        }
        else
        {
            QThread::msleep(m_interval - update_ms);
        }
    }

    m_enabled = false;
}

Command Worker::workerRandom()
{
    // Choose any random position
    switch (rand() % (3 + 1))
    {
    case 0:
        return Command::MOVE_LEFT;
    case 1:
        return Command::MOVE_RIGHT;
    case 2:
        return Command::MOVE_UP;
    default:
    case 3:
        return Command::MOVE_DOWN;
    }
}

Command Worker::workerPureMonteCarlo()
{
    Solver solv;

    // Get the Board as Int-Vector
    std::vector<std::vector<int> > board = m_game->getBoard()->getBoardAsInt();

    // Get best direction from solver
    Solver::Direction bestDirection = solv.getBestDirection(board, 100);

    switch (bestDirection)
    {
        case Solver::Direction::LEFT:
            return Command::MOVE_LEFT;
        break;

        case Solver::Direction::RIGHT:
            return Command::MOVE_RIGHT;
        break;

        case Solver::Direction::UP:
            return Command::MOVE_UP;
        break;

        case Solver::Direction::DOWN:
            return Command::MOVE_DOWN;
        break;

        default:
            return Command::IDLE;
    }
}
