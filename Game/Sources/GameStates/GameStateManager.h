#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include <memory>
#include <stack>

class GameStateManager
{
public:
	void update();
	void render(sf::RenderTarget &target) const;

	void push(std::unique_ptr<GameState> game_state);
	void pop();

private:
	std::stack<std::unique_ptr<GameState>> game_states;
};

#endif