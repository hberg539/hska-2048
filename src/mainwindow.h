#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include "gui/qboard.h"
#include "core/game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    // Spiel
    Game * m_game;

    // Spielbrett
    QBoard * m_qboard;
};

#endif // MAINWINDOW_H
