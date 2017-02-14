#include "qsolver.h"
#include "ui_solver.h"

/**
 * @brief Constructor of QSolver
 * @param parent
 */
QSolver::QSolver(QWidget *parent) :
    QDialog(parent),
    ui                      (new Ui::QSolver),
    m_num_commands          (0),
    m_worker                (new Worker)
{
    ui->setupUi(this);

    // Connect
    connect(m_worker, SIGNAL(sendKeyEvent(QKeyEvent*)), parent, SLOT(recvKeyEvent(QKeyEvent *)));
    connect(m_worker, SIGNAL(sendKeyEvent(QKeyEvent*)), this,   SLOT(recvKeyEvent(QKeyEvent *)));

    // Stop Worker und setze Standardwerte
    stop();

    // Fuege Combolist Eintraege hinzu
    ui->comboAlgorithm->addItem("Random Algorithm", QVariant((int)Algorithm::ALGO_RANDOM));
    ui->comboAlgorithm->addItem("Pure Monte Carlo", QVariant((int)Algorithm::ALGO_PURE_MONTE_CARLO));
    ui->comboAlgorithm->addItem("Right Down", QVariant((int)Algorithm::ALGO_RIGHT_DOWN));
}

void QSolver::recvKeyEvent(QKeyEvent *event)
{
    m_num_commands++;
    ui->numCommands->setText(QString::number(m_num_commands));

    if (event->key() == Qt::Key_Up)    ui->latestCommand->setText("KEY_UP");
    if (event->key() == Qt::Key_Right) ui->latestCommand->setText("KEY_RIGHT");
    if (event->key() == Qt::Key_Down)  ui->latestCommand->setText("KEY_DOWN");
    if (event->key() == Qt::Key_Left)  ui->latestCommand->setText("KEY_LEFT");

    if (!m_worker->m_enabled) stop();
}

QSolver::~QSolver()
{
    delete ui;
}

void QSolver::stop(void)
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonSingle->setEnabled(true);

    // Stop Worker
    m_worker->m_enabled = false;
}

void QSolver::start(void)
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonSingle->setEnabled(false);

    // Reset number of commands
    m_num_commands = 0;
    ui->numCommands->setText(QString::number(m_num_commands));

    // Start Worker
    m_worker->m_enabled = true;
    m_worker->setGame(m_game);
    m_worker->setInterval(ui->spinBoxInterval->value());
    m_worker->setAlgorithm((Algorithm)ui->comboAlgorithm->currentData().toInt());
    m_worker->start();
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
    m_worker->m_single = true;
    m_worker->m_enabled = true;
    m_worker->setGame(m_game);
    m_worker->setInterval(ui->spinBoxInterval->value());
    m_worker->setAlgorithm((Algorithm)ui->comboAlgorithm->currentData().toInt());
    m_worker->start();
}
