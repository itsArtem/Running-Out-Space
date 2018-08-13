#include "World.h"

#include "Tiles/GrassTile.h"
#include "Tiles/WaterTile.h"

#include "../Game.h"

#include "../Entities/Player.h"

#include "../Entities/Bottle.h"
#include "../Entities/UselessItem.h"
#include "../Entities/SpeedPotion.h"

#include "../GameStates/GameStateManager.h"

extern Game game;

World::World(GameStateManager &game_state_manager)
{
	for (int x = -1; x < 4; ++x)
		for (int y = -10; y < 20; ++y)
			tiles.push_back(std::make_unique<WaterTile>(sf::Vector2i(x, y)));

	for (int x = 17; x < 21; ++x)
		for (int y = -10; y < 20; ++y)
			tiles.push_back(std::make_unique<WaterTile>(sf::Vector2i(x, y)));

	for (int x = 5; x < 16; ++x)
		for (int y = -10; y < 20; ++y)
		{
			tiles.push_back(std::make_unique<GrassTile>(sf::Vector2i(4, y), GrassTile::Left));
			tiles.push_back(std::make_unique<GrassTile>(sf::Vector2i(x, y), GrassTile::Basic));
			tiles.push_back(std::make_unique<GrassTile>(sf::Vector2i(16, y), GrassTile::Right));
		}

	entity_manager.add(std::make_unique<Player>(sf::Vector2f(game.get_window_size().x / 2.2f,
		game.get_window_size().y / 1.5f), entity_manager, game_state_manager));
}

void World::update()
{
	for (int tile = 0; tile < tiles.size(); ++tile)
		tiles.at(tile)->update();

	if (std::rand() % 15 == 1)
	{
		int x = std::rand() % 670;

		if (x < 180)
			x = 180 + std::rand() % 400;

		if (std::rand() % 100 < 30)
			entity_manager.add(std::make_unique<Bottle>(sf::Vector2f(static_cast<float>(x), -50.0f)));
		else if (std::rand() % 110 < 10)
			entity_manager.add(std::make_unique<SpeedPotion>(sf::Vector2f(static_cast<float>(x), -50.0f)));
		else 
			entity_manager.add(std::make_unique<UseLessItem>(sf::Vector2f(static_cast<float>(x), -50.0f)));
	}

	entity_manager.update();
}

void World::render(sf::RenderTarget &target) const
{
	for (auto &tile : tiles)
		tile->render(target);

	entity_manager.render(target);
}