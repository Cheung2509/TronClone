#pragma once
#include <SFML\Graphics.hpp>

#include <vector>

#include <Game\TronGame.h>
#include "Trail.h"

class PlayerSprite;

class Renderer
{
public:
	Renderer();
	~Renderer() = default;

	void draw(sf::RenderWindow*, TronGame*);

private:
	PlayerSprite* player1;
	PlayerSprite* player2;

	sf::Font font;
	
	sf::Text player1Score;
	sf::Text player2Score;
	
	Trail trail1;
	Trail trail2;

	float frameRate;
	sf::Clock clock;
	sf::Text fps;

	sf::Text countdown;

	sf::RectangleShape boundary;
};
