#include "worker.h"

Worker::Worker() :
    m_enabled   (false),
    m_single    (false),
    m_num_cycles (0)
{
    srand(time(0));
}

void Worker::run()
{
    Solver solva(0);
    Command lastdirc = Command::MOVE_DOWN;

    m_num_cycles = 0;
    unsigned int x = 0;
    unsigned int points_last = 0;
    while (m_enabled)
    {
        // Start counter
        QTime update_start;
        update_start.start();

        // Command
        Command command = Command::IDLE;

        // Store current cycle count
        uint64_t cycles_start = __rdtsc();

        // Run Alogrithm
        switch (m_algorithm_selected)
        {
            case Algorithm::ALGO_RANDOM:
                command = workerRandom();
            break;

            case Algorithm::ALGO_PURE_MONTE_CARLO:
                command = workerPureMonteCarlo();
                break;

            case Algorithm::ALGO_RIGHT_DOWN:
                command = workerRightDown(solva);
                printf("Hallo Right\n");
                break;
        }

        // Add to cycle counter
        m_num_cycles += __rdtsc() - cycles_start;

        // Output
        unsigned int points = m_game->getPoints();
        x += points - points_last;
        if (x > 20)
        {
            std::cout << points << "\t" << m_num_cycles << std::endl;
            x = 0;
        }

        points_last = points;

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

    std::cout << "number of cycles: " << m_num_cycles << std::endl;

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

Command Worker::workerRightDown(Solver &solva)
{
    int a=0;
    //Solver solv(0);
     std::vector<std::vector<int> > board = m_game->getBoard()->getBoardAsInt();

    Solver::Direction Direction;
    printf("if possible\n");
    if(!solva.isRightDownPossible(board))
    {
        //todo id last row is full move down otherwise move right
        Direction = Solver::Direction::LEFT;
        solva.setlastDirection(0);
    }
    else if(solva.compareDiagonalTiles(board)&&solva.compareNumberTiles(board,0)
            && solva.getlastDirection()==1 && solva.checkRowMerge(board))
    {
        printf("compare Tiles success\n");
        Direction = Solver::Direction::LEFT;
        solva.setlastDirection(3);
    }
    else if(solva.mergevertical(board) && solva.compareNumberTiles(board,1))
        Direction = Solver::Direction::DOWN;
    else
    {
        a=solva.getlastDirection();
        Direction = solva.getDirection(a);
        if(a==0)
        {
            solva.setlastDirection(1);
        }
        else
        {
            solva.setlastDirection(0);
        }
    }
    //switch between right and down direction. otherwise go left.
    printf("go direction\n");
    switch (Direction)
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
