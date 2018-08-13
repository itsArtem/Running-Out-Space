#ifndef GRASS_TILE_H
#define GRASS_TILE_H

#include "Tile.h"
#include <SFML/Graphics/Sprite.hpp>

class GrassTile : public Tile
{
public:
	enum Type
	{
		Basic,Left, Right
	};

	GrassTile(const sf::Vector2i &position, const Type &type);

	void update() override;
	void render(sf::RenderTarget &target) const override;

private:
	sf::Sprite sprite;
};

#endif