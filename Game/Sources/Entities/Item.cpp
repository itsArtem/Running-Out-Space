#include "Item.h"

Item::Item(const std::string &id, const sf::Vector2f &position, const sf::Vector2f &size,
	const sf::Vector2f &scale) : Entity(id, position, size, scale)
{
}