#include "GameStateManager.h"
#include <iostream>

void GameStateManager::update()
{
	if (!game_states.empty())
		game_states.top()->update();
}

void GameStateManager::render(sf::RenderTarget &target) const
{
	if (!game_states.empty())
		game_states.top()->render(target);
}

void GameStateManager::push(std::unique_ptr<GameState> game_state)
{
	if (!game_states.empty())
		game_states.top()->suspend();

	game_states.push(std::move(game_state));
}

void GameStateManager::pop()
{
	if (game_states.empty())
	{
		std::cerr << "Unable to pop game state stack. Reason: stack is empty.\n";
		return;
	}

	game_states.pop();
	
	if (!game_states.empty())
		game_states.top()->resume();
}
