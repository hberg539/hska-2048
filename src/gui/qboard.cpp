#include "gui/qboard.h"

/**
 * @brief Constructor for class QBoard
 * @param board
 */
QBoard::QBoard(Board *board)
    : m_board   (board),
      m_layout  (NULL)
{
    // Init
    init();
}

/**
 * @brief Update dimension and initialize m_layout_tiles from m_board
 */
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

/**
 * @brief Update QBoard with new QTiles from m_board.
 *
 * Method is run everytime a move is applied.
 */
void QBoard::update(void)
{
    // Loesche altes Layout, wenn es existiert
    if (m_layout != NULL) delete m_layout;

    // Passe die Dimension an, sofern sie sich gaendert hat
    int init_done = false;
    if (m_layout_tiles.size() != m_board->getDimension())
    {
        init();
        init_done = true;
    }

    // Erstelle neues Layout
    m_layout = new QGridLayout(this);

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            // Loesche alte QTile (sofern sich die Dimension nicht geaendert hat)
            if (!init_done) delete m_layout_tiles[i][j];

            // Fuege Tiles vom Board hinzu
            m_layout_tiles[i][j] = new QTile(m_board->getTile(i, j));

            // Fuege QTiles in das Layout
            m_layout->addWidget(m_layout_tiles[i][j], i, j);
        }
    }
}
