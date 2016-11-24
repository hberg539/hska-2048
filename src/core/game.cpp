#include "core/game.h"

Game::Game(int dimension)
    : m_state   (Game::State::GAME_RUNNING)
{
    // Init Board
    m_board = new Board(dimension);

    // Reset Game
    resetGame(dimension);
}


bool Game::handleMove(Board::Direction direction)
{
    // Testen, ob ueberhaupt eine Bewegung moeglich ist
    if (!m_board->isAnotherMovePossible())
    {
        m_state = State::GAME_LOST;
        return false;
    }

    // Bewegung durchfuehren
    bool has_moved = m_board->move(direction);

    // Testen, ob ein Tile >= 2048 ist
    // -> dann ist das Spiel gewonnen
    if (isGameWon())
    {
        m_state = State::GAME_WON;
    }

    // Ein neues Tile soll erscheinen,
    // sofern eine Bewegung passiert ist
    if (has_moved)
    {
        m_board->addRandomTile();
    }

    return true;
}

void Game::resetGame(void)
{
    m_board->clear();

    // Fuege erste Tiles hinzu
    m_board->addRandomTile();
    m_board->addRandomTile();
}

void Game::resetGame(int dimension)
{
    // Aendere dimension
    m_board->updateDimension(dimension);

    // Setze zurueck
    resetGame();
}

bool Game::isGameWon(void)
{
    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                if (m_board->getTile(i, j)->getValue() >= 2048)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Gebe Punktestand zurueck
// Original: Punkte entspricht den Wert aller Upgrades
// Unsere Version: Einfach nur die Werte aller Tiles
unsigned int Game::getPoints(void)
{
    unsigned int points = 0;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                points += m_board->getTile(i, j)->getValue();
            }
        }
    }
    return points;
}

void Game::debugPrint(void)
{
    std::cout << "Points: " << getPoints() << std::endl;
    std::cout << "Current board state:" << std::endl;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        for (unsigned int j = 0; j < m_board->getDimension(); j++)
        {
            if (m_board->getTile(i, j) != NULL)
            {
                std::printf("|%4d", m_board->getTile(i, j)->getValue());
            }
            else
            {
                std::cout << "|    ";
            }

        }
        std::cout << "|" << std::endl;
    }

    for (unsigned int i = 0; i < m_board->getDimension(); i++)
    {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;
}
