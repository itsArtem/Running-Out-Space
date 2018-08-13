#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <memory>
#include <vector>

class EntityManager
{
public:
	void update();
	void render(sf::RenderTarget &target) const;

	void add(std::unique_ptr<Entity> entity);

	Entity &get_entity(unsigned int index) const;
	unsigned int get_count();

private:
	std::vector<std::unique_ptr<Entity>> entities;
};

#endif