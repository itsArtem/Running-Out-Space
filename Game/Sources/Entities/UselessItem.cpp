#include "UselessItem.h"
#include "../Resources/Resources.h"

UseLessItem::UseLessItem(const sf::Vector2f &position) : Item("Useless Item", position, sf::Vector2f(16.0f, 16.0f),
	sf::Vector2f(1.5f, 1.5f))
{
	if (!textures.has("Useless Item"))
		textures.load("Useless Item", "Resources/Images/Entities/UselessItem.png");

	sprite.setTexture(textures.get("Useless Item"));

	sprite.scale(scale);
	sprite.setRotation(std::rand() % 360);
}

void UseLessItem::update()
{
	position.y += 4.0f;
	sprite.setPosition(position);

	if (position.y > 540.0f)
		active = false;
}

void UseLessItem::render(sf::RenderTarget &target) const
{
	target.draw(sprite);
}
