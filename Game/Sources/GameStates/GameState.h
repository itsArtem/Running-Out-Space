#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics/RenderTarget.hpp>

class GameState
{
public:
	virtual void update() = 0;
	virtual void render(sf::RenderTarget &target) const = 0;

	virtual void suspend() = 0;
	virtual void resume() = 0;
};

#endif