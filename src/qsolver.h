#ifndef QSOLVER_H
#define QSOLVER_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <algorithm>
#include "core/game.h"
#include "solver.h"
#include "worker.h"
#include "definitions.h"

namespace Ui {
class QSolver;
}

class QSolver : public QDialog
{
    Q_OBJECT

public:
    // Konstruktor
    QSolver(QWidget *parent = 0);
    ~QSolver();

    // Setze Game Instanz
    void setGame(Game * game)
    { m_game = game; }

    // Start / Stop Method
    void start(void);
    void stop(void);

public slots:
     void recvKeyEvent(QKeyEvent * event);

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonSingle_clicked();

private:
    Ui::QSolver *ui;

    // Count number of commands
    unsigned int m_num_commands;

    // Worker Instanz
    Worker * m_worker;

    // Game instanz
    Game * m_game;
};

#endif // QSOLVER_H
