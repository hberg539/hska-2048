/**
 * @file gui/qtile.h
 * @brief Graphical proxy class for core/qtile.h
 */

#ifndef QTILE_H
#define QTILE_H

#include <QObject>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include "core/tile.h"
#include <iostream>
#include <QDialog>
#include <QVBoxLayout>
/**
 * @brief Tile class, Graphical proxy class for core/tile.h
 */
class QTile : public QLabel
{
    Q_OBJECT

public:

    // Konstruktor
    QTile(Tile * tile);

    // Aktualisiere Label-Text und Farben
    void update();

    // Easter Egg
    void mouseDoubleClickEvent(QMouseEvent *event)
    {   if (m_tile->getValue() != 2048) return;
        QDialog * buttonBox = new QDialog();
        buttonBox->setStyleSheet("border-image: url(:/res/pepe.jpg) 0 0 0 0 stretch stretch;");
        buttonBox->showFullScreen();
     }

private:

    // Tile Objekt
    Tile * m_tile;
};

#endif // QTILE_H
