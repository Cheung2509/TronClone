#pragma once
#include <SFML\System\Vector2.hpp>

class GameObject
{
public:
	virtual ~GameObject() = default;

	//Setters
	void setPosition(sf::Vector2f & pos);
	//Getters
	sf::Vector2f getPosition() const;

protected:
	GameObject() = default;
	sf::Vector2f position;
	
};