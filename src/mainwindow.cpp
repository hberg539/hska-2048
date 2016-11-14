#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisiere das Spiel
    m_game = new Game(4);

    // Initialisiere das Spielbrett
    m_qboard = new QBoard(m_game->getBoard());

    // Fuege QBoard an Layout an
    ui->layoutBoard->addWidget(m_qboard);

    m_qboard->update();
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    switch (k->key())
    {
    case Qt::Key_Up:
        m_game->handleMove(m_game->getBoard()->Direction::UP);
        break;

    case Qt::Key_Left:
        m_game->handleMove(m_game->getBoard()->Direction::LEFT);
        break;

    case Qt::Key_Right:
        m_game->handleMove(m_game->getBoard()->Direction::RIGHT);
        break;

    case Qt::Key_Down:
        m_game->handleMove(m_game->getBoard()->Direction::DOWN);
        break;
    }

    // Aktualisiere Widget
    m_qboard->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
