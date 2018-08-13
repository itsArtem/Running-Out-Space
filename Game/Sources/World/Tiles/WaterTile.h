#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "Tile.h"
#include "../../Animation.h"

class WaterTile : public Tile
{
public:
	WaterTile(const sf::Vector2i &pos);

	void update() override;
	void render(sf::RenderTarget &target) const;

private:
	Animation animation;
};

#endif