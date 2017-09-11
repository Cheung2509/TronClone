#pragma once
#include <SFML\Graphics.hpp>

#include <memory>

#include "Player.h"
#include "GameState.h"

namespace sf
{
	class Packet;
}

class TronGame
{
public:
	TronGame();
	~TronGame() = default;

	void playerInput(int&, Direction&);

	void tick(sf::Time&);
	void checkhit();

	//Setters
	void setGameState(GameState);
	//Getters
	GameState getGameState() const;
	Player getPlayer1() const;
	Player getPlayer2() const;
	int getCountDown() const;

	void addTrail();

	friend sf::Packet& operator <<(sf::Packet& packet, const TronGame& game);
	friend sf::Packet& operator >>(sf::Packet& packet, TronGame& game);
	//This is to transfer data from packet if it is a pointer
	friend sf::Packet& operator >> (sf::Packet& packet, TronGame* game);
private:
	GameState state;
	Player player1;
	Player player2;

	float countDown;

	std::vector<sf::Vector2i> trail;
};