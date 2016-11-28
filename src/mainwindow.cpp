#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent),
    ui          (new Ui::MainWindow),
    ui_solver   (new QSolver(this)),
    ui_newgame  (new newgame(this))
{
    ui->setupUi(this);

    // Initialisiere das Spiel
    m_game = new Game(4);

    // Initialisiere das Spielbrett
    m_qboard = new QBoard(m_game->getBoard());

    // Fuege QBoard an Layout an
    ui->layoutBoard->addWidget(m_qboard);

    m_qboard->update();

    // uebergebe lable an newgame
    ui_newgame->setLabel(ui->labelPoints);
    // Neuer Name
    ui->labelName->setText(QString("2048 Game"));

    // Konfiguriere Stylesheet fuer die Labels
    ui->labelName->setStyleSheet("QLabel { color: rgb(119,110,101); font: bold; font: 14pt; }");
    ui->labelPoints->setStyleSheet("QLabel { color: rgb(119,110,101); font: bold; font: 14pt; }");
    ui->labelPoints->setAlignment(Qt::AlignRight);

    // Uebergebe Game Instanz zum Solver
    ui_solver->setGame(m_game);
    ui_newgame->setGame(m_game);
    ui_newgame->setqboard(m_qboard);
}

void MainWindow::slotTest(QKeyEvent *event)
{
    //QMessageBox::information(this, "Loeser laeuft!", "Ja tut er!");
    handleKeyPress(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    handleKeyPress(event);
}

void MainWindow::handleKeyPress(QKeyEvent *k)
{   
    // Spielstatus davor
    Game::State game_state = m_game->getState();

    // Fuehre Bewegung durch
    switch (k->key())
    {
    case Qt::Key_Up:
        m_game->handleMove(Board::Direction::UP);
        break;

    case Qt::Key_Left:
        m_game->handleMove(Board::Direction::LEFT);
        break;

    case Qt::Key_Right:
        m_game->handleMove(Board::Direction::RIGHT);
        break;

    case Qt::Key_Down:
        m_game->handleMove(Board::Direction::DOWN);
        break;
    }

    // Aktualisiere Widget
    m_qboard->update();

    // Aktualisiere Punkte
    ui->labelPoints->setText(QString("Punkte: ") + QString::number(m_game->getPoints()));

    // Spiel gewonnen
    // Gewinn-Fenster nur einmal anzeigen
    if (game_state != m_game->getState()
            && m_game->getState() == Game::State::GAME_WON)
    {
       QMessageBox::information(this, "Gewonnen!", "Spiel gewonnen!");
    }

    // Spiel verloren
    if (m_game->getState() == Game::State::GAME_LOST)
    {
        QMessageBox::information(this, "Verloren!", "Spiel verloren!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Game_triggered()
{
    ui_newgame->show();
}

void MainWindow::on_actionStart_Solver_triggered()
{
    ui_solver->show();
}

void MainWindow::on_actionLoad_Savegame_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "//", "All files (*.*)");
    QString returnmsgqstring;
    string filenamestr, returnmsg;

    filenamestr = filename.toStdString();

    if ((m_game->load(filenamestr, returnmsg)) == true)
    {
        //Loesche altes Spielbrett
        delete m_qboard;

        // Initialisiere das Spielbrett
        m_qboard = new QBoard(m_game->getBoard());

        // Fuege QBoard an Layout an
        ui->layoutBoard->addWidget(m_qboard);

        m_qboard->update();

    }
    else
    {

    }

    returnmsgqstring = QString::fromStdString(returnmsg);

    QMessageBox::information(this, tr("File load"), returnmsgqstring);

}
