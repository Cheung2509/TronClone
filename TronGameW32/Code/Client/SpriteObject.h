#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class SpriteObject
{
public:
	SpriteObject() = default;
	~SpriteObject() = default;

	void loadTexture(std::string fileName);
	virtual void loadTexture() = 0;

	//setters
	void setSpritePosition(sf::Vector2f&);
	//getters
	sf::Sprite getSprite();
	sf::Texture getTexture();
protected:
	sf::Sprite sprite;
	sf::Texture texture;
};