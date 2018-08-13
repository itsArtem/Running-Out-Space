#ifndef RESOURCE_H
#define RESOURCE_H

#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Audio/SoundBuffer.hpp>

extern ResourceManager<sf::Texture> textures;
extern ResourceManager<sf::Font> fonts;

extern ResourceManager<sf::SoundBuffer> sound_buffers;

#endif