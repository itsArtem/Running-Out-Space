#include "PlayState.h"

#include <SFML/Window/Keyboard.hpp>
#include "PauseState.h"

#include "../Resources/Resources.h"

PlayState::PlayState(GameStateManager &game_state_manager) : world(game_state_manager), 
game_state_manager(game_state_manager)
{
	click.setBuffer(sound_buffers.get("Click"));
}

void PlayState::update()
{
	world.update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		click.play();
		game_state_manager.push(std::make_unique<PauseState>(game_state_manager));
	}
}

void PlayState::render(sf::RenderTarget &target) const
{
	world.render(target);
}

void PlayState::suspend()
{
}

void PlayState::resume()
{
}