#include "solver.h"
#include "ui_solver.h"

Solver::Solver(QWidget *parent) :
    QDialog(parent),
    ui                      (new Ui::Solver),
    m_algorithm_selected    (Algorithm::SOLVE_RANDOM),
    m_timer                 (new QTimer)
{
    ui->setupUi(this);

    // Connect
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(this, SIGNAL(sendeTest(QKeyEvent *)), parent, SLOT(slotTest(QKeyEvent *)));
}

void Solver::update(void)
{
    Command command = Command::IDLE;

    // Run Alogrithm
    switch (m_algorithm_selected)
    {
        case Algorithm::SOLVE_RANDOM:
             command = algorithmRandom();
        break;
    }

    // Apply command
    switch (command)
    {
        case Command::MOVE_LEFT:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier,"");
            emit sendeTest(event);
        }
        case Command::MOVE_RIGHT:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier,"");
            emit sendeTest(event);
        }
        case Command::MOVE_UP:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier,"");
            emit sendeTest(event);
        }
        case Command::MOVE_DOWN:
        {
            QKeyEvent * event = new QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier,"");
            emit sendeTest(event);
        }
        break;
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


Solver::~Solver()
{
    delete ui;
}

void Solver::on_pushButtonStart_clicked()
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);

    // Start Timer
    m_timer->setInterval(ui->spinBoxInterval->value());
    m_timer->start();
}

void Solver::on_pushButtonStop_clicked()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);

    // Stop timer
    m_timer->stop();
}
