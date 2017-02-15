/**
 * @file mainwindow.h
 * @brief Main Window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include "gui/qboard.h"
#include "core/game.h"
#include "qsolver.h"
#include "newgame.h"
#include "about.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief MainWindows class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void handleKeyPress(QKeyEvent * event);
    void updateGame();

public slots:
     void recvKeyEvent(QKeyEvent * event);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_actionStart_Solver_triggered();
    void on_actionNew_Game_triggered();
    void on_actionLoad_Savegame_triggered();
    void on_actionExitr_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    // Solver Fenster
    QSolver * ui_solver;

    //newgame Fenster
    newgame * ui_newgame;

    // Spiel
    Game * m_game;

    //About Window
    about * ui_about;

    // Spielbrett
    QBoard * m_qboard;
};

#endif // MAINWINDOW_H
