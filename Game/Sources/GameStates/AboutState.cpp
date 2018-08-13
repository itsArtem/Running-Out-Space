#include "AboutState.h"
#include "../Resources/Resources.h"

#include "../Game.h"

extern Game game;

AboutState::AboutState(GameStateManager &game_state_manager) : game_state_manager(game_state_manager)
{
	click.setBuffer(sound_buffers.get("Click"));

	title.setCharacterSize(24);
	title.setString("About");
	title.setFont(fonts.get("Default"));
	title.setPosition(sf::Vector2f(game.get_window_size().x / 2.2f, 50.0f));

	about.setCharacterSize(16);
	about.setString("Running Out of Space is a game made in 48 hours from\nscratch by Artem Katerynych for the 42nd Ludum Dare.\nThe game was completed on August 12, 2018.");
	about.setFont(fonts.get("Default"));
	about.setPosition(sf::Vector2f(game.get_window_size().x / 6.0f, 130.0f));

	back.setCharacterSize(20);
	back.setString("Back");
	back.setFont(fonts.get("Default"));
	back.setPosition(sf::Vector2f(game.get_window_size().x / 2.11f, 400.0f));
}

void AboutState::update()
{
	if (sf::IntRect(sf::Vector2i(back.getPosition().x, back.getPosition().y),
		sf::Vector2i(64, 18)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (back.getFillColor() != sf::Color(255, 80, 80))
			back.setFillColor(sf::Color(255, 80, 80));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click.play();
			game_state_manager.pop();
		}
	}
	else if (back.getFillColor() != sf::Color::White)
		back.setFillColor(sf::Color::White);
}

void AboutState::render(sf::RenderTarget &target) const
{
	target.draw(title);
	target.draw(about);

	target.draw(back);
}

void AboutState::suspend()
{
}

void AboutState::resume()
{
}
