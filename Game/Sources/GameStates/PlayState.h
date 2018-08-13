#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameStateManager.h"
#include "../World/World.h"

#include <SFML/System/Clock.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

class PlayState : public GameState
{
public:
	PlayState(GameStateManager &game_state_manager);

	void update() override;
	void render(sf::RenderTarget &target) const override;

	void suspend() override;
	void resume() override;

private:
	World world;
	GameStateManager &game_state_manager;

	sf::Sound click;
};

#endif