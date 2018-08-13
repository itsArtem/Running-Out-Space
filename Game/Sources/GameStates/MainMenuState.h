#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameState.h"
#include "GameStateManager.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

class MainMenuState : public GameState
{
public:
	MainMenuState(GameStateManager &game_state_manager);

	void update() override;
	void render(sf::RenderTarget &target) const override;

	void suspend() override;
	void resume() override;

private:
	sf::Text title, play, about, quit, info;
	GameStateManager &game_state_manager;

	sf::Sound click;
};

#endif