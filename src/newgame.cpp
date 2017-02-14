#include "newgame.h"
#include "ui_newgame.h"
#include "mainwindow.h"

/**
 * @brief Constructor for newgame window
 * @param parent
 */
newgame::newgame(QWidget *parent):

    QDialog(parent),
     ui (new Ui::newgame)
{
    ui->setupUi(this);
}

/**
 * @brief Deconstructor from the window newgame
 */
newgame::~newgame(){
    delete ui;
}
/**
 * @brief Start on Button "OK" push event the function
 *        start_newgame()
 */
void newgame::on_pushButton_newgame_clicked(){
    start_newgame();
}

/**
 * @brief Closed the Window "NewGame" when Button "Abbrechen" push event
 *        occurs;
 */
void newgame::on_pushButton_abbrechen_clicked(){
    newgame::close();
}

/**
 * @brief Depending on the value from the spinbox, a new game with the dimension starts
 *        or a when the value is wrong a error message appears
 */
void newgame::start_newgame(){
    if(ui->spinBox->value()>8)
    {
        QMessageBox::information(this, "Error", "Spielfeldgroesse zu gross");
    }
    else if(ui->spinBox->value()>=2)
    {
        m_game->resetGame(ui->spinBox->value());
        m_qboard->update();
        newlabel->setText(QString("Punkte: ") + QString::number(m_game->getPoints()));
        newgame::close();
    }
    else
        QMessageBox::information(this, "Error", "Spielfeldgroesse zu klein");

}
