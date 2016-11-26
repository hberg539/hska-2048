#include "qsolver.h"
#include "ui_solver.h"

QSolver::QSolver(QWidget *parent) :
    QDialog(parent),
    ui                      (new Ui::QSolver),
    m_algorithm_selected    (Algorithm::ALGO_RANDOM),
    m_timer                 (new QTimer),
    m_num_commands          (0)
{
    ui->setupUi(this);

    // Connect
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(this, SIGNAL(sendeTest(QKeyEvent *)), parent, SLOT(slotTest(QKeyEvent *)));

    // Stop Solver und setze Standardwerte
    stop();

    // Fuege Combolist Eintraege hinzu
    ui->comboAlgorithm->addItem("Random Algorithm", QVariant((int)Algorithm::ALGO_RANDOM));
    ui->comboAlgorithm->addItem("Only Left & Right", QVariant((int)Algorithm::ALGO_LEFT_RIGHT));
    ui->comboAlgorithm->addItem("Simple Algorithm", QVariant((int)Algorithm::ALGO_SIMPLE));
}

void QSolver::update(void)
{
    Command command = Command::IDLE;

    // Run Alogrithm
    switch (m_algorithm_selected)
    {
        case Algorithm::ALGO_RANDOM:
             command = algorithmRandom();
            break;
        case Algorithm::ALGO_LEFT_RIGHT:
            command = algorithmLeftRight();
            break;
        case Algorithm::ALGO_SIMPLE:
            command = algorithmSimple();
            break;
    }

    // Add command to history
    m_command_history.push_back(command);

    // Apply command
    switch (command)
    {
        case Command::MOVE_LEFT:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier, "");
            ui->latestCommand->setText("MOVE_LEFT");
            emit sendeTest(event);
            break;
        }
        case Command::MOVE_RIGHT:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier, "");
            ui->latestCommand->setText("MOVE_RIGHT");
            emit sendeTest(event);
            break;
        }
        case Command::MOVE_UP:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, "");
            ui->latestCommand->setText("MOVE_UP");
            emit sendeTest(event);
            break;
        }
        case Command::MOVE_DOWN:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier, "");
            ui->latestCommand->setText("MOVE_DOWN");
            emit sendeTest(event);
            break;
        }
    }

    // Count number of commands
    m_num_commands++;
    ui->numCommands->setText(QString::number(m_num_commands));

    // Beende Solver wenn Spiel gewonnen oder verloren ist
    if (m_game->getState() != Game::State::GAME_RUNNING)
    {
        // Stoppe Solver
        stop();
        return;
    }
}

QSolver::Command QSolver::algorithmRandom()
{
    // Choose any random position
    int output = (rand() % (int)(3 + 1));

    switch (output)
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

QSolver::Command QSolver::algorithmLeftRight()
{
    // Choose any random position
    int output = (rand() % (int)(1 + 1));

    switch (output)
    {
    case 0:
        return Command::MOVE_LEFT;
    default:
    case 1:
        return Command::MOVE_RIGHT;
    }
}

QSolver::Command QSolver::algorithmSimple()
{

    // If the last move was UP, instantly move DOWN again
    if (m_command_history.size() > 0 && m_command_history[m_command_history.size() - 1] == Command::MOVE_UP)
    {
        std::cout << "Recovering from last UP command" << std::endl;
        return Command::MOVE_DOWN;
    }

    // Get the Board as Int-Vector
    std::vector<std::vector<int> > board = m_game->getBoard()->getBoardAsInt();

    if (m_command_history.size() > 0 && m_command_history[m_command_history.size() - 1] == Command::MOVE_DOWN)
    {
        if (solver.isMovePossible(board, solver.Direction::RIGHT)) return Command::MOVE_RIGHT;
        return Command::MOVE_UP;
    }

    return Command::MOVE_DOWN;

    /*// Test 3 Directions
    unsigned int pointsLeft = solver.evaluateMove(board, solver.Direction::LEFT);
    unsigned int pointsRight = solver.evaluateMove(board, solver.Direction::RIGHT);
    unsigned int pointsDown = solver.evaluateMove(board, solver.Direction::DOWN);

    // Get move with highest point
    unsigned int pointsMax = std::max(pointsLeft, std::max(pointsRight, pointsDown));

    // At this point, no move makes any points
    if (pointsMax == 0)
    {
        if (solver.isMovePossible(board, solver.Direction::LEFT)) return Command::MOVE_LEFT;
        if (solver.isMovePossible(board, solver.Direction::DOWN)) return Command::MOVE_DOWN;
        if (solver.isMovePossible(board, solver.Direction::RIGHT)) return Command::MOVE_RIGHT;
        if (solver.isMovePossible(board, solver.Direction::UP)) return Command::MOVE_UP;
    }
    // Some specific move makes points
    else
    {
        if (pointsMax == pointsLeft)
        {
            std::cout << "Best move is LEFT with " << pointsLeft << " points" << std::endl;
            return Command::MOVE_LEFT;
        }

        if (pointsMax == pointsRight)
        {
            std::cout << "Best move is RIGHT with " << pointsRight << " points" << std::endl;
            return Command::MOVE_RIGHT;
        }

        if (pointsMax == pointsDown)
        {
            std::cout << "Best move is DOWN with " << pointsDown << " points" << std::endl;
            return Command::MOVE_DOWN;
        }
    }*/

    return Command::IDLE;
}

QSolver::~QSolver()
{
    delete ui;
}

void QSolver::stop(void)
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);

    // Stop timer
    m_timer->stop();
}

void QSolver::start(void)
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);

    // Reset number of commands
    m_num_commands = 0;
    ui->numCommands->setText(QString::number(m_num_commands));

    // Start Timer
    m_timer->setInterval(ui->spinBoxInterval->value());
    m_timer->start();
}

void QSolver::on_pushButtonStart_clicked()
{
    start();
}

void QSolver::on_pushButtonStop_clicked()
{
    stop();
}

void QSolver::on_pushButtonSingle_clicked()
{
    // Run only one time
    update();
}

void QSolver::on_comboAlgorithm_currentIndexChanged(int index)
{
    // Get selected algorithm
    m_algorithm_selected = (Algorithm)ui->comboAlgorithm->currentData().toInt();
}