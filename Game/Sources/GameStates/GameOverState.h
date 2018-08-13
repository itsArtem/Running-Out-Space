#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameStateManager.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

class GameOverState : public GameState
{
public:
	GameOverState(GameStateManager &game_state_manager, unsigned int final_score);

	void update() override;
	void render(sf::RenderTarget &target) const override;

	void suspend() override;
	void resume() override;

private:
	sf::Text title, retry, main_menu, score;
	GameStateManager &game_state_manager;

	sf::Sound click;
};

#endif