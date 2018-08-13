#include "SpeedPotion.h"
#include "../Resources/Resources.h"

SpeedPotion::SpeedPotion(const sf::Vector2f &position) : Item("Speed Potion", position,
	sf::Vector2f(16.0f, 16.0f), sf::Vector2f(1.5f, 1.5f))
{
	if (!textures.has("Potions"))
		textures.load("Potions", "Resources/Images/Entities/Potions.png");
	
	sprite.setTexture(textures.get("Potions"));
	sprite.setTextureRect(sf::IntRect(size.x, 0, size.x, size.y));
	sprite.setPosition(position);
	sprite.scale(scale);

	sprite.setRotation(std::rand() % 360);
}

void SpeedPotion::update()
{
	position.y += 4.0f;
	sprite.setPosition(position);

	if (position.y > 540.0f)
		active = false;
}

void SpeedPotion::render(sf::RenderTarget &target) const
{
	target.draw(sprite);
}