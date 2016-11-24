#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include "gui/qboard.h"
#include "core/game.h"
#include "solver.h"

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

private:
    Ui::MainWindow *ui;

    // Solver Fenster
    Solver * ui_solver;

    // Spiel
    Game * m_game;

    // Spielbrett
    QBoard * m_qboard;
};

#endif // MAINWINDOW_H
