#include "MainMenuState.h"
#include "../Resources/Resources.h"

#include "../Game.h"
#include <SFML/Window/Mouse.hpp>

#include "PlayState.h"
#include "AboutState.h"

extern Game game;

MainMenuState::MainMenuState(GameStateManager &game_state_manager) : game_state_manager(game_state_manager)
{
	if (!fonts.has("Default"))
		fonts.load("Default", "Resources/Fonts/Default.ttf");

	if (!sound_buffers.has("Click"))
		sound_buffers.load("Click", "Resources/Audio/Click.wav");

	click.setBuffer(sound_buffers.get("Click"));

	title.setCharacterSize(24);
	title.setString("RUNNING OUT OF SPACE");
	title.setFont(fonts.get("Default"));
	title.setPosition(sf::Vector2f(game.get_window_size().x / 3.4f, 50.0f));

	play.setString("Play");
	play.setFont(fonts.get("Default"));
	play.setCharacterSize(18);
	play.setPosition(sf::Vector2f(100.0f, 200.0f));
	title.setOutlineThickness(2.0f);
	title.setOutlineColor(sf::Color(80, 80, 80));

	info.setString("Move around with the A and D keys.\nYou can use potions to increase the\nplayer speed temporary. The more\nyou drink, the greater the affect is.\nAvoid picking up items for as long as\nposible!");
	info.setFont(fonts.get("Default"));
	info.setCharacterSize(16);
	info.setPosition(sf::Vector2f(360.0f, 200.0f));

	about.setString("About");
	about.setFont(fonts.get("Default"));
	about.setCharacterSize(18);
	about.setPosition(sf::Vector2f(100.0f, 240.0f));

	quit.setString("Quit");
	quit.setFont(fonts.get("Default"));
	quit.setCharacterSize(18);
	quit.setPosition(sf::Vector2f(100.0f, 280.0f));
}

void MainMenuState::update()
{
	if (sf::IntRect(sf::Vector2i(play.getPosition().x, play.getPosition().y),
		sf::Vector2i(64, 18)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (play.getFillColor() != sf::Color(255, 80, 80))
			play.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.push(std::make_unique<PlayState>(game_state_manager));
		}
	}
	else if (play.getFillColor() != sf::Color::White)
		play.setFillColor(sf::Color::White);

	if (sf::IntRect(sf::Vector2i(about.getPosition().x, about.getPosition().y),
		sf::Vector2i(79, 18)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (about.getFillColor() != sf::Color(255, 80, 80))
			about.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.push(std::make_unique<AboutState>(game_state_manager));
		}
	}
	else if (about.getFillColor() != sf::Color::White)
		about.setFillColor(sf::Color::White);

	if (sf::IntRect(sf::Vector2i(quit.getPosition().x, quit.getPosition().y),
		sf::Vector2i(64, 18)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (quit.getFillColor() != sf::Color(255, 80, 80))
			quit.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();

			while (click.getStatus() == click.Playing)
				;

			game.stop();
		}
	}
	else if (quit.getFillColor() != sf::Color::White)
		quit.setFillColor(sf::Color::White);
}

void MainMenuState::render(sf::RenderTarget &target) const
{
	target.draw(title);

	target.draw(play);
	target.draw(about);
	target.draw(quit);

	target.draw(info);
}

void MainMenuState::suspend()
{
}

void MainMenuState::resume()
{
}