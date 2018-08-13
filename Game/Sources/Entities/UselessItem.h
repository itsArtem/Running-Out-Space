#ifndef USELESS_ITEM_H
#define USELESS_ITEM_H

#include "Item.h"
#include <SFML/Graphics/Sprite.hpp>

class UseLessItem : public Item
{
public:
	UseLessItem(const sf::Vector2f &position);
	
	void update() override;
	void render(sf::RenderTarget &target) const override;

private:
	sf::Sprite sprite;
};

#endif