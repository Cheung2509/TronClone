#include "TronGame.h"
#include <SFML\Network.hpp>

sf::Packet& operator<<(sf::Packet& packet, const TronGame& game)
{
	return packet << game.state << game.player1 << game.player2 << game.countDown;
}

sf::Packet& operator >> (sf::Packet& packet, TronGame& game)
{
	return packet >> game.player1 >> game.player2;
}

sf::Packet& operator >> (sf::Packet& packet, TronGame* game)
{
	return packet >> game->player1 >> game->player2 >> game->countDown;
}

TronGame::TronGame()
{
	state = GAME_START;
	player1.setPlayerID(0);
	player2.setPlayerID(2);
	
	player1.setResetPos(sf::Vector2f(125, 250));
	player2.setResetPos(sf::Vector2f(375, 250));

	player1.resetPosition();
	player2.resetPosition();

	player2.setDirection(Direction::LEFT);

	countDown = 4;

}

void TronGame::playerInput(int & id, Direction & dir)
{
	if (player1.getPlayerID() == id)
	{
		player1.processInput(dir);
	}
	else if (player2.getPlayerID() == id)
	{
		player2.processInput(dir);
	}
}

void TronGame::tick(sf::Time& deltaTime)
{
	//check the game state
	if (state == GameState::GAME_START)
	{
		countDown -= deltaTime.asSeconds();
		if (countDown <= 0)
		{
			state = GameState::GAME_PLAY;
		}
	}
	if (state == GameState::GAME_PLAY)
	{
		if (player1.getIsAlive() && player2.getIsAlive())
		{
			player1.processMovement(deltaTime);
			player2.processMovement(deltaTime);
			checkhit();
			addTrail();
		}
		else
		{
			if (!player1.getIsAlive())
			{
				player2.incrementRoundsWon();
			}
			else if (!player2.getIsAlive())
			{
				player1.incrementRoundsWon();
			}
			setGameState(GameState::GAME_ROUND_OVER);
		}
	}
	else if (state == GameState::GAME_PAUSE)
	{
		//Do nothing
	}
	else if (state == GameState::GAME_ROUND_OVER)
	{
		player1.resetPosition();
		player1.setIsAlive(true);
		player1.setDirection(Direction::RIGHT);

		player2.resetPosition();
		player2.setIsAlive(true);
		player2.setDirection(Direction::LEFT);

		state = GameState::GAME_START;
		countDown = 4;

		trail.clear();
	}
}

void TronGame::checkhit()
{
	for (auto& pos : trail)
	{
		if (player1.checkHit(pos))
		{
			player1.setIsAlive(false);
		}
		
		if (player2.checkHit(pos))
		{
			player2.setIsAlive(false);
		}
	}

	
}

void TronGame::setGameState(GameState gState)
{
	state = gState;
}

GameState TronGame::getGameState() const
{
	return state;
}

Player TronGame::getPlayer1() const
{
	return player1;
}

Player TronGame::getPlayer2() const
{
	return player2;
}

int TronGame::getCountDown() const
{
	return countDown;
}

void TronGame::addTrail()
{
	//Add trail behind player depending on direction the player is moving
	if (player1.getDirection() == Direction::LEFT)
	{
		trail.push_back(sf::Vector2i(player1.getPosition().x + 1, player1.getPosition().y));
	}
	else if (player1.getDirection() == Direction::UP)
	{
		trail.push_back(sf::Vector2i(player1.getPosition().x, player1.getPosition().y + 1));
	}
	else if (player1.getDirection() == Direction::RIGHT)
	{
		trail.push_back(sf::Vector2i(player1.getPosition().x - 1, player1.getPosition().y));
	}
	else if (player1.getDirection() == Direction::DOWN)
	{
		trail.push_back(sf::Vector2i(player1.getPosition().x, player1.getPosition().y - 1));
	}

	if (player2.getDirection() == Direction::LEFT)
	{
		trail.push_back(sf::Vector2i(player2.getPosition().x + 1, player2.getPosition().y));
	}
	else if (player2.getDirection() == Direction::UP)
	{
		trail.push_back(sf::Vector2i(player2.getPosition().x, player2.getPosition().y + 1));
	}
	else if (player2.getDirection() == Direction::RIGHT)
	{
		trail.push_back(sf::Vector2i(player2.getPosition().x - 1, player2.getPosition().y));
	}
	else if (player2.getDirection() == Direction::DOWN)
	{
		trail.push_back(sf::Vector2i(player2.getPosition().x, player2.getPosition().y - 1));
	}
}
