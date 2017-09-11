#pragma once
#include <SFML\Graphics.hpp>


class Menu
{
public:
	Menu();
	~Menu() = default;

	void draw(sf::RenderWindow*);

private:
	sf::Font font;
	sf::Text menu[3];
};