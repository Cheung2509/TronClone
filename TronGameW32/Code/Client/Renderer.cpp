#include "Renderer.h"
#include "PlayerSprite.h"
#include "Trail.h"

Renderer::Renderer()
{
	player1 = new PlayerSprite(sf::Color::Green);
	player2 = new PlayerSprite(sf::Color::Red);
	
	//Loading font
	if (!font.loadFromFile("./Resources/arial.ttf"))
	{
		//error
	}

	//Setting font for text
	player1Score.setFont(font);
	player2Score.setFont(font);
	fps.setFont(font);
	countdown.setFont(font);

	//Setting character size for text
	player1Score.setCharacterSize(25);
	player2Score.setCharacterSize(25);
	fps.setCharacterSize(15);
	countdown.setCharacterSize(25);

	//Setting colors of stuff
	player1Score.setFillColor(sf::Color::Green);
	player2Score.setFillColor(sf::Color::Red);
	fps.setFillColor(sf::Color::White);
	countdown.setFillColor(sf::Color::Red);
	trail1.setColor(sf::Color::Green);
	trail2.setColor(sf::Color::Red);
	
	//Setting position of text
	player1Score.setPosition(125, 500);
	player2Score.setPosition(375, 500);
	countdown.setPosition(250, 250);

	//Setting color of stuff
	boundary.setFillColor(sf::Color::Transparent);
	boundary.setOutlineColor(sf::Color::White);
	boundary.setOutlineThickness(5);
	boundary.setSize(sf::Vector2f(500,500));
}

void Renderer::draw(sf::RenderWindow * window, TronGame * game)
{
	if (game->getGameState() == GameState::GAME_START)
	{
		//Draw countdown
		std::string string = std::to_string(game->getCountDown());
		countdown.setString(string);
		window->draw(countdown);
		trail1.clearVertex();
		trail2.clearVertex();

	}
	else if (game->getGameState() == GameState::GAME_PLAY)
	{
		//Draw the players
		player1->setShapePos(game->getPlayer1().getPosition());
		player2->setShapePos(game->getPlayer2().getPosition());

		//Draw the trail
		trail1.addVertex(game->getPlayer1().getPosition());
		trail2.addVertex(game->getPlayer2().getPosition());

		//Draw all elements of game
		window->draw(player1->getShape());
		window->draw(player2->getShape());
		window->draw(trail1);
		window->draw(trail2);
	}
	else if (game->getGameState() == GameState::GAME_ROUND_OVER)
	{
		//Clear all players color
		window->clear(sf::Color::Red);
		window->clear(sf::Color::Green);
	}

	//calculate and draw framerate
	frameRate = 1.f / clock.getElapsedTime().asSeconds();
	std::string string;
	string = std::to_string(frameRate);
	fps.setString(string);

	//Set Plater score text
	string = std::to_string(game->getPlayer1().getRoundsWon());
	player1Score.setString(string);
	string = std::to_string(game->getPlayer2().getRoundsWon());
	player2Score.setString(string);

	//Draw everything
	window->draw(boundary);
	window->draw(fps);
	window->draw(player1Score);
	window->draw(player2Score);
	
	//restart the clock to calculate framerate every frame
	clock.restart();
}
