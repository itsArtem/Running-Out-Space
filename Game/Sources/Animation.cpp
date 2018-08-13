#include "Animation.h"
#include <iostream>

Animation::Animation() : index(0), ms_frame_delay(0.0f)
{
}

Animation::Animation(sf::Texture &sprite_sheet, const sf::Vector2f &size, const sf::Vector2u &start,
	unsigned int sprite_count, float ms_frame_delay) : sprite(sprite_sheet, sf::IntRect(0, 0, static_cast<int>(size.x),
		static_cast<int>(size.y))), size(size), start(start), sprite_count(sprite_count), index(0)
{
	set_frame_delay(ms_frame_delay);	
}

void Animation::set_sprite_sheet(sf::Texture &sprite_sheet, const sf::Vector2f &size, 
	const sf::Vector2u &start, unsigned sprite_count)
{
	this->size = size;
	this->sprite_count = sprite_count;
	
	sprite = sf::Sprite(sprite_sheet, sf::IntRect(start.x * size.x, start.y * size.y, 
		static_cast<int>(size.x), static_cast<int>(size.y)));
}

void Animation::set_frame_delay(float ms_frame_delay)
{
	if (ms_frame_delay < 0.0f)
	{
		std::cerr << "Animation delay cannot be negetive.\n";
		ms_frame_delay = 0.0f;
	}
	
	this->ms_frame_delay = ms_frame_delay;
}

void Animation::scale(const sf::Vector2f &factors)
{
	sprite.scale(factors);
}

void Animation::rotate(float factor)
{
	sprite.rotate(factor);
}

const sf::Vector2f &Animation::get_position() const
{
	return sprite.getPosition();
}

void Animation::set_position(const sf::Vector2f &position)
{
	sprite.setPosition(position);
}

void Animation::move(const sf::Vector2f &factors)
{
	sprite.move(factors);
}

void Animation::restart()
{
	if (index != 0)
		index = 0;
}

void Animation::update()
{
	if (frame_timer.getElapsedTime().asMilliseconds() >= ms_frame_delay)
	{
		index = index + 1 < sprite_count ? ++index : 0;
		sprite.setTextureRect(sf::IntRect(static_cast<int>(start.x != 0 ? start.x : 1 * size.x) * index, 
			static_cast<int>(size.y) * start.y, static_cast<int>(size.x), static_cast<int>(size.y)));

		frame_timer.restart();
	}
}

void Animation::render(sf::RenderTarget &target) const
{
	target.draw(sprite);
}
