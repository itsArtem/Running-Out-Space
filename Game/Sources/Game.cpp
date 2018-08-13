#include "Game.h"
#include "GameStates/MainMenuState.h"

#include <SFML/Audio/Music.hpp>

Game::Game() : window(sf::VideoMode(840, 620), "Running Out of Space", sf::Style::Titlebar | sf::Style::Close)
{
	window.setFramerateLimit(60);
}

void Game::run()
{
	game_state_manager.push(std::make_unique<MainMenuState>(game_state_manager));

	sf::Music theme;
	theme.openFromFile("Resources/Audio/Theme.wav");

	theme.setLoop(true);
	theme.setVolume(30.0f);

	theme.play();

	while (window.isOpen())
	{
		update();
		render();
	}
}

const sf::Vector2u &Game::get_window_size() const
{
	return window.getSize();
}

const sf::Event::EventType &Game::get_event_type() const
{
	return event.type;
}

const sf::Window &Game::get_window() const
{
	return window;
}

const sf::View &Game::get_window_view() const
{
	return window.getView();
}

void Game::stop()
{
	window.close();
}

void Game::update()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	game_state_manager.update();
}

void Game::render()
{
	window.clear();
	game_state_manager.render(window);
	window.display();
}