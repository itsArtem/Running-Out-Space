#include "PauseState.h"
#include "../Resources/Resources.h"

#include "../Game.h"
#include "MainMenuState.h"

extern Game game;

PauseState::PauseState(GameStateManager &game_state_manager) : game_state_manager(game_state_manager)
{
	click.setBuffer(sound_buffers.get("Click"));

	messege.setCharacterSize(24);
	messege.setString("Paused");
	messege.setFont(fonts.get("Default"));
	messege.setPosition(sf::Vector2f(game.get_window_size().x / 2.4f, 150.0f));

	resume_game.setCharacterSize(20);
	resume_game.setString("Resume");
	resume_game.setFont(fonts.get("Default"));
	resume_game.setPosition(sf::Vector2f(game.get_window_size().x / 2.33f, 360.0f));

	main_menu.setCharacterSize(20);
	main_menu.setString("Main Menu");
	main_menu.setFont(fonts.get("Default"));
	main_menu.setPosition(sf::Vector2f(game.get_window_size().x / 2.405f, 400.0f));
}

void PauseState::update()
{
	if (sf::IntRect(sf::Vector2i(resume_game.getPosition().x, resume_game.getPosition().y),
		sf::Vector2i(100, 24)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (resume_game.getFillColor() != sf::Color(255, 80, 80))
			resume_game.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.pop();
		}
	}
	else if (resume_game.getFillColor() != sf::Color::White)
		resume_game.setFillColor(sf::Color::White);

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
}

void PauseState::render(sf::RenderTarget &target) const
{
	target.draw(messege);

	target.draw(resume_game);
	target.draw(main_menu);
}

void PauseState::suspend()
{
}

void PauseState::resume()
{
}
