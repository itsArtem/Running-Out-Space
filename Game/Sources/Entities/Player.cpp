#include "Player.h"
#include "../Resources/Resources.h"

#include <SFML/Window/Keyboard.hpp>
#include "../Game.h"

#include "../World/Tiles/Tile.h"
#include "Item.h"

#include "Bottle.h"

#include <SFML/Window/Mouse.hpp>
#include "../GameStates/GameOverState.h"

extern Game game;

Player::Player(const sf::Vector2f &position, EntityManager &entity_manager,
	GameStateManager &game_state_manager) : Entity("Player", position,
		sf::Vector2f(16.0f, 16.0f), sf::Vector2f(4.5f, 4.5f)), normal_speed(4.0f), current_speed(normal_speed),
	entity_manager(entity_manager), game_state_manager(game_state_manager), inventory(*this), score(0)
{
	if (!sound_buffers.has("Game Over"))
		sound_buffers.load("Game Over", "Resources/Audio/GameOver.wav");

	if (!sound_buffers.has("Pickup"))
		sound_buffers.load("Pickup", "Resources/Audio/Pickup.wav");

	game_over.setBuffer(sound_buffers.get("Game Over"));
	pickup.setBuffer(sound_buffers.get("Pickup"));

	if (!textures.has("Player"))
		textures.load("Player", "Resources/Images/Entities/Player.png");

	if (!fonts.has("Default"))
		fonts.load("Default", "Resources/Fonts/Default.ttf");

	alert.setCharacterSize(24);
	alert.setString("RUNNING OUT OF SPACE!");
	alert.setFont(fonts.get("Default"));
	alert.setPosition(sf::Vector2f(game.get_window_size().x / 3.4f, 50.0f));

	animation.set_sprite_sheet(textures.get("Player"), size, sf::Vector2u(), 2);
	animation.set_frame_delay(150.0f);
	animation.scale(scale);

	score_text.setPosition(sf::Vector2f(game.get_window_size().x - 130.0f, 10.0f));
	score_text.setCharacterSize(16);
	score_text.setFont(fonts.get("Default"));
	score_text.setString("Score " + std::to_string(score));
}

void Player::update()
{
	static sf::Clock score_timer;

	if (score > 1000)
	{
		if (score_text.getString() != "Max score")
			score_text.setString("Max score");
	}
	else
	{
		if (score_timer.getElapsedTime().asSeconds() >= 3.0f)
		{

			if (score < 1000)
			{
				++score;
				score_text.setString("Score " + std::to_string(score));
			}
			score_timer.restart();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position.x > 140.0f)
		position.x -= current_speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position.x < 620.0f)
		position.x += current_speed;

	if (animation.get_position() != position)
		animation.set_position(position);

	animation.update();
	inventory.update();

	for (int e = 0; e < entity_manager.get_count(); ++e)
		if (Item *i = dynamic_cast<Item *>(&entity_manager.get_entity(e)))
		{
			sf::FloatRect bounds(position, sf::Vector2f(size.x * scale.x, size.y * scale.y));

			sf::FloatRect item_bounds(i->get_position(), sf::Vector2f(0.5f, 1.0f));

			if (bounds.intersects(item_bounds))
				if (!inventory.is_full())
				{
					pickup.play();

					inventory.add(i->id);
					entity_manager.get_entity(e).active = false;

					if (score > 0)
					{
						--score;
						score_text.setString("Score " + std::to_string(score));
					}
					else
						score_timer.restart();
				}
		}

	if (inventory.is_full())
	{
		game_over.play();

		active = false;
		game_state_manager.push(std::make_unique<GameOverState>(game_state_manager, score));
		return;
	}

	if (current_speed != normal_speed)
	{
		static sf::Clock timer;

		if (timer.getElapsedTime().asSeconds() >= 8.0f)
		{
			current_speed -= 3.0f;
			timer.restart();
		}
	}

	if (inventory.get_item_count() >= 8)
	{
		static sf::Vector2f amount;

		if (std::rand() % 2 == 0)
			++amount.x;
		else
			++amount.y;

		if (amount.x >= 2.0f)
			amount.x = -2.0f;

		if (amount.y >= 2.0f)
			amount.y = -2.0f;

		static sf::Vector2f old_position = alert.getPosition();
		alert.setPosition(sf::Vector2f(old_position.x + amount.x, old_position.y + amount.y));
	}
}

void Player::render(sf::RenderTarget &target) const
{
	animation.render(target);
	inventory.render(target);

	if (inventory.get_item_count() >= 8)
		target.draw(alert);

	target.draw(score_text);
}

Player::Inventory::Inventory(Player &player) : full(false), item_count(0)
{
	for (int i = 0; i < 10; ++i)
		slots.push_back(Slot(sf::Vector2f((i * -56) + (game.get_window_size().x / 1.3f) - 0.8f,
			game.get_window_size().y - 56.4f), player));
}

void Player::Inventory::update()
{
	for (auto &slot : slots)
		slot.update();

	if (item_count >= 8)
	{
		static sf::Vector2f amount;

		if (std::rand() % 2 == 0)
			++amount.x;
		else
			++amount.y;

		if (amount.x >= 2.0f)
			amount.x = -2.0f;

		if (amount.y >= 2.0f)
			amount.y = -2.0f;

		slots.at(0).sprite.setPosition(sf::Vector2f(slots.at(0).position.x + amount.x,
			slots.at(0).position.y + amount.y));

		if (item_count == 8)
			slots.at(1).sprite.setPosition(sf::Vector2f(slots.at(1).position.x + amount.y,
				slots.at(1).position.y + amount.x));
		else
			if (slots.at(1).sprite.getPosition() != slots.at(1).position)
				slots.at(1).sprite.setPosition(slots.at(1).position);
	}
}

void Player::Inventory::render(sf::RenderTarget &target) const
{
	for (auto &slot : slots)
		slot.render(target);
}

void Player::Inventory::add(const std::string &id)
{
	for (int i = slots.size() - 1; i >= 0; --i)
	{
		if (!slots.at(i).has_item())
		{
			if (i == 0)
				full = true;

			slots.at(i).add_item(id);
			++item_count;
			return;
		}
	}
}

bool Player::Inventory::is_full() const
{
	return full;
}

unsigned int Player::Inventory::get_item_count() const
{
	return item_count;
}

Player::Inventory::Slot::Slot(const sf::Vector2f &position, Player &player) : position(position), player(player),
item_id("None"), size(16.0f, 16.0f), scale(3.5f, 3.5f)
{
	if (!textures.has("Slot"))
		textures.load("Slot", "Resources/Images/Entities/Player.png");

	sprite.setTexture(textures.get("Slot"));
	sprite.setTextureRect(sf::IntRect(0, size.y, size.x, size.y));

	sprite.scale(scale);
	sprite.setPosition(position);

	if (!sound_buffers.has("Potion"))
		sound_buffers.load("Potion", "Resources/Audio/Potion.wav");

	if (!sound_buffers.has("Unuseable"))
		sound_buffers.load("Unuseable", "Resources/Audio/Unuseable.wav");

	potion.setBuffer(sound_buffers.get("Potion"));
	unuseable.setBuffer(sound_buffers.get("Unuseable"));
}

void Player::Inventory::Slot::update()
{
	if (sf::IntRect(sf::Vector2i(position.x, position.y),
		sf::Vector2i(size.x * scale.x, size.y * scale.y)).contains(sf::Mouse::getPosition(game.get_window())))
	{
		if (sprite.getColor() != sf::Color(190, 190, 190))
			sprite.setColor(sf::Color(190, 190, 190));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (item_id == "Speed Potion")
			{
				potion.play();

				player.current_speed += 3.0f;
				item_id = "Bottle";
			}
			else
				unuseable.play();
		}
	}
	else if (sprite.getColor() != sf::Color::White)
		sprite.setColor(sf::Color::White);
}

void Player::Inventory::Slot::render(sf::RenderTarget &target) const
{
	target.draw(sprite);

	if (item_id == "Bottle")
	{
		sf::Sprite item(textures.get("Potions"), sf::IntRect(0, 0, 16, 16));
		item.setPosition(sf::Vector2f(position.x + 14.0f, position.y + 11.0f));
		item.scale(sf::Vector2f(2.0f, 2.0f));
		target.draw(item);
	}
	else if (item_id == "Useless Item")
	{
		sf::Sprite item(textures.get("Useless Item"), sf::IntRect(0, 0, 16, 16));
		item.setPosition(sf::Vector2f(position.x + 12.0f, position.y + 10.0f));
		item.scale(sf::Vector2f(2.0f, 2.0f));
		target.draw(item);
	}
	else if (item_id == "Speed Potion")
	{
		sf::Sprite item(textures.get("Potions"), sf::IntRect(16, 0, 16, 16));
		item.setPosition(sf::Vector2f(position.x + 14.0f, position.y + 11.0f));
		item.scale(sf::Vector2f(2.0f, 2.0f));
		target.draw(item);
	}
}

bool Player::Inventory::Slot::has_item() const
{
	return item_id != "None";
}

void Player::Inventory::Slot::add_item(const std::string &id)
{
	item_id = id;
}