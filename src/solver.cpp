#include "solver.h"
#include "ui_solver.h"

Solver::Solver(QWidget *parent) :
    QDialog(parent),
    ui                      (new Ui::Solver),
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
}

void Solver::update(void)
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
    }

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

Solver::Command Solver::algorithmRandom()
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

Solver::Command Solver::algorithmLeftRight()
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

Solver::~Solver()
{
    delete ui;
}

void Solver::stop(void)
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);

    // Stop timer
    m_timer->stop();
}

void Solver::start(void)
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);

    // Get selected algorithm
    m_algorithm_selected = (Algorithm)ui->comboAlgorithm->currentData().toInt();

    // Reset number of commands
    m_num_commands = 0;
    ui->numCommands->setText(QString::number(m_num_commands));

    // Start Timer
    m_timer->setInterval(ui->spinBoxInterval->value());
    m_timer->start();
}

void Solver::on_pushButtonStart_clicked()
{
    start();
}

void Solver::on_pushButtonStop_clicked()
{
    stop();
}
