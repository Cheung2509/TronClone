#include "Player.h"

Player::Player()
{
	roundsWon = 0;
	isAlive = true;
}

void Player::setPlayerID(int id)
{
	player_id = id;
}

void Player::incrementRoundsWon()
{
	++roundsWon;
}

void Player::setDirection(Direction dir)
{
	direction = dir;
}

void Player::setResetPos(sf::Vector2f pos)
{
	resetPos = pos;
}

int Player::getPlayerID() const
{
	return player_id;
}

int Player::getRoundsWon() const
{
	return roundsWon;
}

Direction Player::getDirection() const
{
	return direction;
}

void Player::tick(sf::Time& deltaTime)
{
	//Process the movement of player
	processMovement(deltaTime);
}

void Player::processMovement(sf::Time& deltaTime)
{
	if (direction == Direction::UP)
	{
		position.y -= moveSpeed * deltaTime.asSeconds();
	}
	else if (direction == Direction::RIGHT)
	{
		position.x += moveSpeed * deltaTime.asSeconds();
	}
	else if (direction == Direction::DOWN)
	{
		position.y += moveSpeed * deltaTime.asSeconds();
	}
	else if (direction == Direction::LEFT)
	{
		position.x -= moveSpeed * deltaTime.asSeconds();
	}

	if (position.x < 0 || position.y < 0 || position.x >= 500 || position.y > 500)
	{
		isAlive = false;
	}
}

void Player::processInput(Direction & dir)
{
	if ((dir == Direction::UP && direction == Direction::DOWN) ||
		(dir == Direction::DOWN && direction == Direction::UP) ||
		dir == Direction::RIGHT && direction == Direction::LEFT ||
		(dir == Direction::LEFT && direction == Direction::RIGHT))
	{
		//Player cant move to the opposit direction
	}
	else
	{
		//else move to desired direction
		setDirection(dir);
	}
}

void Player::resetPosition()
{
	this->setPosition(resetPos);
}

bool Player::checkHit(sf::Vector2i & pos)
{
	return sf::Vector2i(position.x,position.y) == pos;
}

sf::Packet & operator <<(sf::Packet & packet, const Player & player)
{
	return packet << player.player_id << player.isAlive 
		<< player.roundsWon << player.position.x << player.position.y;
}

sf::Packet & operator >>(sf::Packet & packet, Player & player)
{
	return packet >> player.player_id >> player.isAlive >> player.roundsWon
		>> player.position.x >> player.position.y;
}
