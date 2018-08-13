#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/System/Clock.hpp>

class Animation
{
public:
	Animation();
	Animation(sf::Texture &sprite_sheet, const sf::Vector2f &size, const sf::Vector2u &start, 
		unsigned int sprite_count, float ms_frame_delay);

	void set_sprite_sheet(sf::Texture &sprite_sheet, const sf::Vector2f &size, const sf::Vector2u &start, 
		unsigned sprite_count);
	void set_frame_delay(float ms_frame_delay);

	void scale(const sf::Vector2f &factors);
	void rotate(float factor);
	

	const sf::Vector2f &get_position() const;
	void set_position(const sf::Vector2f &position);
	
	void move(const sf::Vector2f &factors);

	void restart();

	void update();
	void render(sf::RenderTarget &target) const;

private:
	sf::Sprite sprite;
	sf::Vector2f size;
	const sf::Vector2u start;

	unsigned int index;
	unsigned int sprite_count;

	float ms_frame_delay;
	sf::Clock frame_timer;
};

#endif