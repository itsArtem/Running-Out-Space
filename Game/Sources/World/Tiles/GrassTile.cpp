#include "GrassTile.h"
#include "../../Resources/Resources.h"

GrassTile::GrassTile(const sf::Vector2i &position, const Type &type) : Tile(position)
{
	if (!textures.has("Grass"))
		textures.load("Grass", "Resources/Images/Tiles/Grass.png");

	sprite.setTexture(textures.get("Grass"));
	sprite.scale(scale);
	sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * size.x * scale.x),
		static_cast<float>(position.y * size.y * scale.y)));

	switch (type)
	{
	case Basic:
		sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		break;

	case Left:
		sprite.setTextureRect(sf::IntRect(static_cast<int>(size.x) * 2, 0, static_cast<int>(size.x),
			static_cast<int>(size.y)));
		break;

	case Right:
		sprite.setTextureRect(sf::IntRect(static_cast<int>(size.x) * 2, 0, static_cast<int>(size.x),
			static_cast<int>(size.y)));
		sprite.rotate(180.0f);
		sprite.move(sf::Vector2f(-size.x * -scale.x, -size.y * -scale.y));
		break;
	}
}

void GrassTile::update() 
{
	// Huge hack. (Running out of time!)
	sprite.move(sf::Vector2f(0.0f, 4.0f));

	if (sprite.getPosition().y > 680.0f)
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x, -(size.y * scale.y)));
}

void GrassTile::render(sf::RenderTarget &target) const
{
	target.draw(sprite);
}