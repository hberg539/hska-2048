#ifndef NEWGAME_H
#define NEWGAME_H

#include "core/game.h"
#include "gui/qboard.h"
#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QMessageBox>

namespace Ui {
class newgame;
}

/**
 * @brief Window to start a new game
 */
class newgame:public QDialog
{
    Q_OBJECT

public:
    newgame(QWidget *parent=0);
    ~newgame();
    void setGame(Game * game)
    { m_game = game; }
    void setqboard(QBoard * qboard)
    { m_qboard = qboard; }

    void setLabel(QLabel * labelpoints)
    { newlabel = labelpoints;}
    void start_newgame();

private slots:
        void on_pushButton_newgame_clicked();
        void on_pushButton_abbrechen_clicked();
private:
    Ui::newgame *ui;
    Game * m_game;
    QBoard * m_qboard;
    QLabel * newlabel;
};

#endif // NEWGAME_H
