#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameStateManager.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

class PauseState : public GameState
{
public:
	PauseState(GameStateManager &game_state_manager);

	void update() override;
	void render(sf::RenderTarget &target) const override;

	void suspend() override;
	void resume() override;

private:
	sf::Text messege, resume_game, main_menu;
	GameStateManager &game_state_manager;

	sf::Sound click;
};

#endif