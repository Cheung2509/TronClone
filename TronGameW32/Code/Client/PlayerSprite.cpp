#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(sf::Color pColor)
{
	shape.setRadius(2.5);
	color = pColor;
	shape.setFillColor(color);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
}

void PlayerSprite::setShapePos(sf::Vector2f & pos)
{
	shape.setPosition(pos);
}
