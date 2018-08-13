#ifndef WORLD_H
#define WORLD_H

#include "Tiles/Tile.h"
#include <memory>
#include <vector>

#include "../Entities/EntityManager.h"
#include "../GameStates/GameStateManager.h"

class World
{
public:
	World(GameStateManager &game_state_manager);

	void update();
	void render(sf::RenderTarget &target) const;
	
private:
	std::vector<std::unique_ptr<Tile>> tiles;
	EntityManager entity_manager;
};

#endif