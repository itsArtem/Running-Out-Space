#include "Tile.h"

const sf::Vector2f Tile::size(16.0f, 16.0f);
const sf::Vector2f Tile::scale(2.5f, 2.5f);

Tile::Tile(const sf::Vector2i &position) : position(position)
{
}