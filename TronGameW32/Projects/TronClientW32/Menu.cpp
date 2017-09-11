#include "Menu.h"

Menu::Menu()
{
	if (font.loadFromFile("arial.ttf"))
	{

	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
}

void Menu::draw(sf::RenderWindow *)
{
	
}
