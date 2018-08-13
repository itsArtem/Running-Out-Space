#ifndef ABOUT_STATE_H
#define ABOUT_STATE_H

#include "GameStateManager.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

class AboutState : public GameState
{
public:
	AboutState(GameStateManager &game_state_manager);

	void update() override;
	void render(sf::RenderTarget &target) const override;

	void suspend() override;
	void resume() override;

private:
	GameStateManager &game_state_manager;
	sf::Text title, about, back;

	sf::Sound click;
};

#endif