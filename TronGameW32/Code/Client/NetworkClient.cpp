#include "NetworkClient.h"

#include <future>

#include <SFML\Window\Keyboard.hpp>

#include <Game\PacketType.h>

int NetworkClient::getID() const
{
	return id;
}

void NetworkClient::runClient(TronGame* cGame)
{
	game = cGame;

	//check if the client can connect to the server
	if (!connect())
	{
		return;
	}
	sf::Socket::Status status;

	do
	{
		sf::Packet packet;
		status = socket.receive(packet);

		if (status == sf::Socket::Done)
		{
			//Check packet type
			int header = 0;
			packet >> header;
			PacketType type = static_cast<PacketType>(header);

			if (type == PacketType::GAME)
			{
				processGamePacket(packet);
			}
			else if (type == PacketType::PING)
			{
				//Send a response packet to server
				sf::Packet pong;
				pong << PacketType::PONG;
				socket.send(pong);
			}
			else if (type == PacketType::ASSIGN_ID)
			{
				//Assigning id of player
				packet >> id;
			}
		}
	} while (status != sf::Socket::Disconnected);
}

bool NetworkClient::connect()
{
	auto status = socket.connect(SERVER_IP, SERVER_TCP_PORT);

	if (status != sf::Socket::Done)
	{
		return false;
	}

	return true;
}

bool NetworkClient::isConnected()
{
	return socket.getLocalPort() != 0;
}


const void NetworkClient::sendInput(Direction& direction)
{
	//Send players input to server
	sf::Packet packet;

	packet << PacketType::GAME << direction;

	socket.send(packet);
}

void NetworkClient::processGamePacket(sf::Packet & packet)
{
	//Update game if the packet type is game
	mtx.lock();
	//Updating game state
	int state = 0;
	packet >> state;
	game->setGameState(static_cast<GameState>(state));
	packet >> game;
	mtx.unlock();
}