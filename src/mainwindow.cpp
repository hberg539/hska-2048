#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

 void MainWindow::keyPressEvent(QKeyEvent *k )
{
    switch( k->key())
    {
        case Qt::Key_Up:
            ui->setLabel(1);
            break;
        case Qt::Key_Down:
            ui->setLabel(2);
            break;
        default:
            ui->setLabel(3);
            break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
