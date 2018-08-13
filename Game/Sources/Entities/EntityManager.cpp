#include "EntityManager.h"
#include <iostream>

void EntityManager::update()
{
	for (int e = 0; e < entities.size(); ++e)
	{
		entities.at(e)->update();
		
		if (!entities.at(e)->active)
			entities.erase(entities.begin() + e);
	}
}

void EntityManager::render(sf::RenderTarget &target) const
{
	for (const auto &entity : entities)
		entity->render(target);
}

void EntityManager::add(std::unique_ptr<Entity> entity)
{
	entities.push_back(std::move(entity));
}

Entity &EntityManager::get_entity(unsigned int index) const
{
	return *entities.at(index);
}

unsigned int EntityManager::get_count()
{
	return entities.size();
}