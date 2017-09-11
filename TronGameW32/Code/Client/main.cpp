#include <SFML/Graphics.hpp>

#include <Game\TronGame.h>

#include "NetworkClient.h"
#include "Renderer.h"

#include <memory>
#include <thread>

void renderingThread(sf::RenderWindow*, TronGame*);
void inputThread(sf::Event& event, NetworkClient&);

//Function to render the scene
void renderingThread(sf::RenderWindow* window, TronGame* game)
{
	Renderer renderer;
	while (window->isOpen())
	{
		window->clear();
		renderer.draw(window, game);
		window->display();
	}
}

void inputThread(sf::Event& event, NetworkClient & network)
{
	if (event.type == sf::Event::KeyPressed)
	{
		Direction direction;
		if (event.key.code == sf::Keyboard::W)
		{
			direction = Direction::UP;
			network.sendInput(direction);
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			direction = Direction::RIGHT;
			network.sendInput(direction);
		}
		else if (event.key.code == sf::Keyboard::S)
		{
			direction = Direction::DOWN;
			network.sendInput(direction);
		}
		else if (event.key.code == sf::Keyboard::A)
		{
			direction = Direction::LEFT;
			network.sendInput(direction);
		}
	}
}

int main()
{
	float windowHeight = 600;
	float windoWidth = 500;

	sf::RenderWindow* window = new sf::RenderWindow(
		sf::VideoMode(windoWidth, windowHeight), 
		"SFML works!");

	window->setActive(false);

	//Creating pointer for game
	TronGame* game = new TronGame();

	//creating thread to create the network client
	NetworkClient network;
	std::thread networkThread(&NetworkClient::runClient, &network, game);


	//Creating thread for rendering
	std::thread renderThread(&renderingThread, window, game);

	//It was running on 1000 - 5000 fps maybe a good idea to limit it.
	window->setFramerateLimit(60);

	while (window->isOpen())
	{
		sf::Event event;

		if (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			//Poll input of player
			inputThread(event, network);
		}
	}

	networkThread.detach();
	renderThread.detach();

	delete game;
	return 0;
}