#include "Entity.h"

Entity::Entity(const std::string &id, const sf::Vector2f &position, const sf::Vector2f &size,
	const sf::Vector2f &scale) : id(id), position(position), size(size), scale(scale), active(true)
{
}

const sf::Vector2f &Entity::get_position() const
{
	return position;
}

const sf::Vector2f &Entity::get_size() const
{
	return size;
}

const sf::Vector2f &Entity::get_scale() const
{
	return scale;
}