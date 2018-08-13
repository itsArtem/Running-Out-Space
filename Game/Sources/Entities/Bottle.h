#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include <SFML/Graphics/Sprite.hpp>

class Bottle : public Item
{
public:
	Bottle(const sf::Vector2f &position);
	
	void update() override;
	void render(sf::RenderTarget &target) const override;

private:
	sf::Sprite sprite;
};

#endif