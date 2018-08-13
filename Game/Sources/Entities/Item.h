#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

// Used to limit what could be added to the inventory.
class Item : public Entity
{
public:
	Item(const std::string &id, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &scale);
};

#endif