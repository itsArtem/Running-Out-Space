#include "GameOverState.h"
#include "../Resources/Resources.h"

#include "../Game.h"

#include "MainMenuState.h"
#include "PlayState.h"

extern Game game;

GameOverState::GameOverState(GameStateManager &game_state_manager, 
	unsigned int final_score) : game_state_manager(game_state_manager)
{
	click.setBuffer(sound_buffers.get("Click"));

	title.setCharacterSize(24);
	title.setString("You ran out of space!");
	title.setFont(fonts.get("Default"));
	title.setPosition(sf::Vector2f(game.get_window_size().x / 3.4f, 50.0f));

	retry.setString("Retry");
	retry.setFont(fonts.get("Default"));
	retry.setCharacterSize(18);
	retry.setPosition(sf::Vector2f(140.0f, 220.0f));

	main_menu.setString("Main Menu");
	main_menu.setFont(fonts.get("Default"));
	main_menu.setCharacterSize(18);
	main_menu.setPosition(sf::Vector2f(140.0f, 260.0f));

	score.setString("You got a final score of " + (final_score < 1000 ? std::to_string(final_score) : "max") + 
		"!\nI bet you can do better!");
	score.setFont(fonts.get("Default"));
	score.setCharacterSize(16);
	score.setPosition(sf::Vector2f(460.0f, 220.0f));
}

void GameOverState::update()
{
	if (sf::IntRect(sf::Vector2i(main_menu.getPosition().x, main_menu.getPosition().y),
		sf::Vector2i(135, 18)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (main_menu.getFillColor() != sf::Color(255, 80, 80))
			main_menu.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.push(std::make_unique<MainMenuState>(game_state_manager));
		}
	}
	else if (main_menu.getFillColor() != sf::Color::White)
		main_menu.setFillColor(sf::Color::White);

	if (sf::IntRect(sf::Vector2i(retry.getPosition().x, retry.getPosition().y),
		sf::Vector2i(80, 24)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (retry.getFillColor() != sf::Color(255, 80, 80))
			retry.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.push(std::make_unique<PlayState>(game_state_manager));
		}
	}
	else if (retry.getFillColor() != sf::Color::White)
		retry.setFillColor(sf::Color::White);
}

void GameOverState::render(sf::RenderTarget &target) const
{
	target.draw(title);
	target.draw(score);

	target.draw(retry);
	target.draw(main_menu);
}

void GameOverState::suspend()
{
}

void GameOverState::resume()
{
}
