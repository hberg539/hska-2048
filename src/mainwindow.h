#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include "gui/qboard.h"
#include "core/game.h"
#include "qsolver.h"
#include "newgame.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void handleKeyPress(QKeyEvent * event);

public slots:
     void slotTest(QKeyEvent * event);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_actionStart_Solver_triggered();
    void on_actionNew_Game_triggered();

    void on_actionLoad_Savegame_triggered();

private:
    Ui::MainWindow *ui;

    // Solver Fenster
    QSolver * ui_solver;

    //newgame Fenster
    newgame * ui_newgame;

    // Spiel
    Game * m_game;

    // Spielbrett
    QBoard * m_qboard;
};

#endif // MAINWINDOW_H
