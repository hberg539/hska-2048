#include "core/tile.h"

/**
 * @brief Constructor of tile class
 * @param value Inital value of the tile
 */
Tile::Tile(int value)
    : m_value          (value),
      m_flag_upgraded  (false)
{
}
