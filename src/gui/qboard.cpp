#include "gui/qboard.h"

QBoard::QBoard(Board *board)
    : m_board   (board),
      m_layout  (NULL)
{
    // Init
    init();
}

void QBoard::init(void)
{
    // Loesche, sofern vorhanden, alte QTiles
    for (unsigned i = 0; i < m_layout_tiles.size(); i++)
    {
        for (unsigned j = 0; j < m_layout_tiles[i].size(); j++)
        {
            delete m_layout_tiles[i][j];
        }
    }

    // Passe die Groesse von m_layout_tiles an
    m_layout_tiles.resize(m_board->getDimension());
    for (unsigned i = 0; i < m_board->getDimension(); i++)
    {
        m_layout_tiles[i].resize(m_board->getDimension());
    }
}

void QBoard::update(void)
{
    // Loesche altes Layout, wenn es existiert
    if (m_layout != NULL) delete m_layout;

    // Erstelle neues Layout
    m_layout = new QGridLayout(this);

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned j = 0; j < m_board->getDimension(); j++)
        {
            // Loesche alte QTile
            delete m_layout_tiles[i][j];

            // Fuege Tiles vom Board hinzu
            m_layout_tiles[i][j] = new QTile(m_board->getTile(i, j));

            // Fuege QTiles in das Layout
            m_layout->addWidget(m_layout_tiles[i][j], i, j);
        }
    }
}
