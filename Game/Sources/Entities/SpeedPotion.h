#ifndef SPEED_POTION_H
#define SPEED_POTION_H

#include "Item.h"
#include <SFML/Graphics/Sprite.hpp>

class SpeedPotion : public Item
{
public:
	SpeedPotion(const sf::Vector2f &position);
	
	void update() override;
	void render(sf::RenderTarget &target) const override;

private:
	sf::Sprite sprite;
};

#endif