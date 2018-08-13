#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameStates/GameStateManager.h"

class Game
{
public:
	Game();
	void run();
	
	const sf::Vector2u &get_window_size() const;
	const sf::Event::EventType &get_event_type() const;

	const sf::Window &get_window() const;

	const sf::View &get_window_view() const;

	void stop();

private:
	sf::RenderWindow window;
	sf::Event event;

	GameStateManager game_state_manager;

	void update();
	void render();
};

#endif