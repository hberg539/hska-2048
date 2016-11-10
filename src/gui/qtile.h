#ifndef QTILE_H
#define QTILE_H

#include <QObject>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include "core/tile.h"


class QTile : public QLabel
{
    Q_OBJECT

public:

    // Konstruktor
    QTile(Tile * tile);

    // Aktualisiere Label-Text und Farben
    void update();

private:

    // Tile Objekt
    Tile * m_tile;
};

#endif // QTILE_H
