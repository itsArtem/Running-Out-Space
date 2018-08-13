#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/RenderTarget.hpp>

class Tile
{
public:
	const sf::Vector2i position;
	static const sf::Vector2f size, scale;

	Tile(const sf::Vector2i &position);

	virtual void update() = 0;
	virtual void render(sf::RenderTarget &target) const = 0;
};

#endif