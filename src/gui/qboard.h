#ifndef QBOARD_H
#define QBOARD_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <vector>
#include "core/board.h"
#include "gui/qtile.h"

class QBoard : public QWidget
{
    Q_OBJECT

public:

    // Konstruktor
    QBoard(Board * board);

    // Init Spielbrett
    void init(void);

    // Aktualisiert / Zeichnet das Spielbrett
    void update(void);

private:

    // Board Objekt
    Board * m_board;

    // Box-Layout
    QGridLayout * m_layout;

    // QTiles vom Layout
    std::vector<std::vector<QTile *> > m_layout_tiles;
};

#endif // QBOARD_H
