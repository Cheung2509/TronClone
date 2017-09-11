#pragma once
#include "SpriteObject.h"

class PlayerSprite
{
public:
	PlayerSprite(sf::Color);
	~PlayerSprite() = default;

	sf::CircleShape getShape() { return shape; }
	void setShapePos(sf::Vector2f& pos);
private:
	sf::Color color;
	sf::CircleShape shape;
};