#include "gui/qtile.h"

/**
 * @brief Constructor for QTile
 * @param tile Input is a Tile (core/tile.h)
 */
QTile::QTile(Tile * tile)
    : m_tile (tile)
{
    // Wert zentriert
    setAlignment(Qt::AlignCenter);

    // Zeichne Stylesheets, etc.
    update();
}

/**
 * @brief Update the color and styling when the value of a tile changes.
 */
void QTile::update()
{
    // Farb-Kodierung schamlos von der Original-Implementierung geklaut
    if (m_tile == NULL)
    {
        setText("");
        setStyleSheet("QTile { background: rgb(204,192,179); border-radius: 10px; }");
    }
    else
    {
        setText(QString::number(m_tile->getValue()));

        switch (m_tile->getValue())
        {
        case 2:
            setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 4:
            setStyleSheet("QTile { background: rgb(237,224,200); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 8:
            setStyleSheet("QTile { background: rgb(242,177,121); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 16:
            setStyleSheet("QTile { background: rgb(245,150,100); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 32:
            setStyleSheet("QTile { background: rgb(245,125,95); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 64:
            setStyleSheet("QTile { background: rgb(245,95,60); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 128:
            setStyleSheet("QTile { background: rgb(237,207,114); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;

        case 256: {
            QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
            dse->setColor(Qt::yellow);
            dse->setBlurRadius(5);
            dse->setOffset(-1);
            setGraphicsEffect(dse);
            setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;
        }

        case 512: {
            QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
            dse->setColor(Qt::yellow);
            dse->setBlurRadius(15);
            dse->setOffset(-1);
            setGraphicsEffect(dse);
            setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;
        }

        case 1024: {
            QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
            dse->setColor(Qt::yellow);
            dse->setBlurRadius(20);
            dse->setOffset(-1);
            setGraphicsEffect(dse);
            setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;
        }

        case 2048: {
            QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
            dse->setColor(Qt::yellow);
            dse->setBlurRadius(50);
            dse->setOffset(-1);
            setGraphicsEffect(dse);
            setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            break;
        }

        case 5:
            setStyleSheet("QTile { background: black; color: black; font: bold; border-radius: 10px; font: 25pt; }");
            break;
        case 15:
            setStyleSheet("QTile { background: red; color: red; font: bold; border-radius: 10px; font: 25pt; }");
            break;
        case 30:
            setStyleSheet("QTile { background: yellow; color: yellow; font: bold; border-radius: 10px; font: 25pt; }");
            break;

        default:
            if (m_tile->getValue() >= 4096)
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::blue);
                dse->setBlurRadius(10);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(0,149,255); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 25pt; }");
            }
            else
            {
                setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 25pt; }");
            }
            break;
        }
    }
}
