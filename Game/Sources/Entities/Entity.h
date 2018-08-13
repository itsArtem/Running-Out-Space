#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

class Entity
{
public:
	const std::string id;
	bool active;

	Entity(const std::string &id, const sf::Vector2f &position, const sf::Vector2f &size,
		const sf::Vector2f &scale);

	virtual void update() = 0;
	virtual void render(sf::RenderTarget &target) const = 0;

	const sf::Vector2f &get_position() const;
	const sf::Vector2f &get_size() const;
	const sf::Vector2f &get_scale() const;

protected:
	sf::Vector2f position, size, scale;
};

#endif