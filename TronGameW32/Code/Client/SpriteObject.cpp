#include "SpriteObject.h"

void SpriteObject::loadTexture(std::string fileName)
{
	if (texture.loadFromFile(fileName))
	{

	}
	sprite.setTexture(texture);
}

void SpriteObject::setSpritePosition(sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

sf::Sprite SpriteObject::getSprite()
{
	return sprite;
}

sf::Texture SpriteObject::getTexture()
{
	return texture;
}
