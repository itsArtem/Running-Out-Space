#include "WaterTile.h"
#include "../../Resources/Resources.h"

WaterTile::WaterTile(const sf::Vector2i &pos) : Tile(pos)
{
	if (!textures.has("Water"))
		textures.load("Water", "Resources/Images/Tiles/Water.png");

	animation.set_sprite_sheet(textures.get("Water"), size, sf::Vector2u(), 3);
	animation.set_frame_delay(150.0f);

	animation.scale(scale);
	animation.set_position(sf::Vector2f(static_cast<float>(pos.x * size.x * scale.x), 
		static_cast<float>(pos.y * size.y * scale.y)));
}

void WaterTile::update()
{
	animation.update();

	animation.move(sf::Vector2f(0.0f, 4.0f));

	if (animation.get_position().y > 620.0f)
		animation.set_position(sf::Vector2f(animation.get_position().x, -(size.y * scale.y)));
}

void WaterTile::render(sf::RenderTarget &target) const
{
	animation.render(target);
}
