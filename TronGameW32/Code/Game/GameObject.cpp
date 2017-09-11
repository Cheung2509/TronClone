#include "GameObject.h"

void GameObject::setPosition(sf::Vector2f & pos)
{
	position = pos;
}

sf::Vector2f GameObject::getPosition() const
{
	return position;
}
