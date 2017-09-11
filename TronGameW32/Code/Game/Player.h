#pragma once
#include "Actor.h"
#include "Direction.h"

#include <SFML\Graphics.hpp>

class Player : public Actor
{
public:
	Player();
	~Player() = default;

	//Setters
	void setPlayerID(int);
	void incrementRoundsWon();
	void setDirection(Direction);
	void setResetPos(sf::Vector2f);

	//Getters
	int getPlayerID() const;
	int getRoundsWon() const;
	Direction getDirection() const;

	void tick(sf::Time&);
	void processMovement(sf::Time&);
	void processInput(Direction&);
	void resetPosition();
	bool checkHit(sf::Vector2i&);

	//Packet operators for sending information about the player
	friend sf::Packet& operator <<(sf::Packet& packet, const Player& player);
	friend sf::Packet& operator >>(sf::Packet& packet, Player& player);
private:
	int player_id;	//Player id
	Direction direction = Direction::RIGHT;	//Direction which the player is moving in
	float moveSpeed = 100.0f;
	int roundsWon;
	sf::Vector2f resetPos;
};