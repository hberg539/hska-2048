#ifndef QSOLVER_H
#define QSOLVER_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <algorithm>
#include "core/game.h"
#include "solver.h"

namespace Ui {
class QSolver;
}

class QSolver : public QDialog
{
    Q_OBJECT

public:

    // Enum fuer Algorithmus
    enum class Algorithm { ALGO_RANDOM, ALGO_LEFT_RIGHT, ALGO_SIMPLE };

    // Enum fuer Command
    enum class Command { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, IDLE };

    // Konstruktor
    QSolver(QWidget *parent = 0);
    ~QSolver();

    // Setze Game Instanz
    void setGame(Game * game)
    { m_game = game; }

    // Start / Stop Method
    void start(void);
    void stop(void);

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void update();

    void on_pushButtonSingle_clicked();

    void on_comboAlgorithm_currentIndexChanged(int index);

signals:
    void sendeTest(QKeyEvent * event);

private:
    Ui::QSolver *ui;

    // Solver instanz
    Solver solver;

    // Game instanz
    Game * m_game;

    // Timer Instanz
    QTimer * m_timer;

    // solver selected
    Algorithm m_algorithm_selected;

    // Count number of commands
    unsigned int m_num_commands;

    // Save command history
    std::vector<Command> m_command_history;

    // Random Algorithm
    Command algorithmRandom(void);

    // Left & Right Algorithm
    Command algorithmLeftRight(void);

    // Einfacher Algorithmus
    Command algorithmSimple(void);
};

#endif // QSOLVER_H
