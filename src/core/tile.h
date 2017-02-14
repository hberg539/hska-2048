/**
 * @file core/tile.h
 * @brief Class represents one tile of the game.
 */

#ifndef TILE_H
#define TILE_H

/**
 * @brief Tile Class, represents one tile of the game
 */
class Tile
{
public:

    // Konstruktor
    Tile(int value);

    // Setze neuen Wert
    void updateValue(const int value)
    { m_value = value; }

    // Gebe Wert zurück
    int  getValue(void)
    { return m_value; }

    // Upgrade Tile (*2)
    void upgrade(void)
    { m_value = m_value * 2; m_flag_upgraded = true; }

    // Wurde das Tile bereits upgraded?
    bool getFlagUpgraded(void)
    { return m_flag_upgraded; }

    // Upgraded-Flag zuruecksetzen
    void resetFlagUpgraded(void)
    { m_flag_upgraded = false; }

private:

    // Wert des Tile
    int m_value;

    // Move-Flag
    bool m_flag_upgraded;

};

#endif // TILE_H
