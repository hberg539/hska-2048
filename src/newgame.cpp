#include "newgame.h"
#include "ui_newgame.h"
#include "mainwindow.h"

newgame::newgame(QWidget *parent):

    QDialog(parent),
     ui (new Ui::newgame)
{
    ui->setupUi(this);
}

newgame::~newgame(){
    delete ui;
}

void newgame::on_pushButton_newgame_clicked(){
    start_newgame();
}

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
        ui->checkBox->setChecked(false);
    }
    else
        QMessageBox::information(this, "Error", "Spielfeldgroesse zu klein");

}
