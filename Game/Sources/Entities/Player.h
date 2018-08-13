#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Animation.h"

#include "Item.h"
#include <vector>

#include "EntityManager.h"
#include <SFML/Graphics/Text.hpp>

#include "../GameStates/GameStateManager.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

class Player : public Entity
{
public:
	Player(const sf::Vector2f &position, EntityManager &entity_manager, GameStateManager &game_state_manager);

	void update() override;
	void render(sf::RenderTarget &target) const override;

private:
	GameStateManager &game_state_manager;

	const float normal_speed;
	float current_speed;

	Animation animation;
	EntityManager &entity_manager;

	unsigned int score;
	sf::Text alert, score_text;

	sf::Sound game_over, pickup;
	
	class Inventory
	{
	public:
		Inventory(Player &player);

		void update();
		void render(sf::RenderTarget &target) const;

		void add(const std::string &id);
		
		bool is_full() const;
		unsigned int get_item_count() const;

	private:
		class Slot
		{
		public:
			Slot(const sf::Vector2f &position, Player &player);

			void update();
			void render(sf::RenderTarget &target) const;

			bool has_item() const;
			void add_item(const std::string &id);


		private:
			friend Inventory;
			friend Player;

			Player &player;
			sf::Sprite sprite;
	
			sf::Sound potion, unuseable;

			sf::Vector2f position;
			const sf::Vector2f size, scale;

			std::string item_id;
		};


		std::vector<Slot> slots;
		
		bool full;
		unsigned int item_count;

	};

	Inventory inventory;
};

#endif