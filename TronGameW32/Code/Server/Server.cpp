#include "Server.h"

#include <Game\PacketType.h>
#include <Game\Direction.h>
#include <Game\TronGame.h>

#include <thread>

void Server::runServer()
{
	if (!this->bindServerPort())
	{
		return;
	}

	selector.add(listener);

	std::thread gameThread(&Server::runGame, this);
	return listen();
}

void Server::runGame()
{
	sf::Clock clock;

	while (true)
	{
		mtx.lock();
		sf::Time deltaTime = clock.restart();
		game.tick(deltaTime);
		sendGameData();
		mtx.unlock();
	}
}

void Server::sendGameData()
{
		if (!tcp_clients.empty())
		{
			if (selector.isReady(listener))
			{
				for (auto& client : tcp_clients)
				{
					sf::Packet packet;
					packet << PacketType::GAME << game;

					client.getSocket().send(packet);
				}
			}
		}
}

void Server::ping()
{
	constexpr auto timeout = 3s;

	for (auto& client : tcp_clients)
	{
		const auto& timestamp = client.getPingTime();
		const auto  now = std::chrono::steady_clock::now();
		auto delta = now - timestamp;
		if (delta > timeout)
		{
			client.ping();
		}
	}
}

bool Server::bindServerPort()
{
	if (listener.listen(SERVER_TCP_PORT) != sf::Socket::Done)
	{
		std::cout << "Could not bind a server port" << std::endl;
		std::cout << "Port: " << SERVER_TCP_PORT << std::endl;
		return false;
	}

	std::cout << "Server successfully binded to port: " << SERVER_TCP_PORT
		<< std::endl;
	return true;
}

void Server::clearStaleClients()
{
	tcp_clients.erase(
		std::remove_if(tcp_clients.begin(), tcp_clients.end(), [](const Client& client)
	{
		return (!client.isConected());
	}), tcp_clients.end());
}

void Server::connect()
{
	mtx.lock();
	auto client_ptr = new sf::TcpSocket;
	auto& client_ref = *client_ptr;

	if (listener.accept(client_ref) == sf::Socket::Done)
	{
		//adding client to selector
		selector.add(client_ref);

		auto client = Client(client_ptr);
		tcp_clients.push_back(std::move(client));
		std::cout << "Client Connected" << std::endl;

		sf::Packet packet;
		packet << PacketType::ASSIGN_ID << client.getClientID();

		client_ref.send(packet);
	}
	mtx.unlock();
}

void Server::receivePacket()
{
	for (auto& sender : tcp_clients)
	{
		auto& sender_socket = sender.getSocket();

		if (selector.isReady(sender_socket))
		{
			sf::Packet packet;

			//If Socket has disconnected
			if (sender_socket.receive(packet) == sf::Socket::Disconnected)
			{
				//Removing disconnected client from selector
				selector.remove(sender_socket);
				sender_socket.disconnect();

				//Server to output which client has disconnected
				std::cout << "Client " << sender.getClientID()
					<< " Disconnected" << std::endl;

				break;
			}

			int header = 0;
			packet >> header;

			PacketType type = static_cast<PacketType>(header);
			if (type == PacketType::GAME)
			{
				processGamePacket(packet, sender);
			}
			else if (type == PacketType::PONG)
			{
				sender.pong();
				std::cout << "Client " << sender.getClientID() << " Latency: " << sender.getLatency().count() << std::endl;
			}
		}
	}
}

void Server::processGamePacket(sf::Packet& packet, Client& sender)
{
	int header = 0;
	packet >> header;

	Direction direction = static_cast<Direction>(header);

	std::cout << "Client " << sender.getClientID() << ":";

	switch (direction)
	{
	case Direction::UP:
		std::cout << "Up" << std::endl;
		break;
	case Direction::RIGHT:
		std::cout << "Right" << std::endl;
		break;
	case Direction::DOWN:
		std::cout << "Down" << std::endl;
		break;
	case Direction::LEFT:
		std::cout << "Left" << std::endl;
		break;
	default:
		break;
	}

	//Update game depending on player input
	int id = sender.getClientID();
	game.playerInput(id, direction);
}

void Server::listen()
{
	while (true)
	{
		const sf::Time timeout = sf::Time(sf::milliseconds(10));
		if (selector.wait(timeout))
		{
			if (selector.isReady(listener))
			{
				connect();
			}
			else
			{
				receivePacket();
				clearStaleClients();
			}
		}
		else
		{
			ping();
		}
	}
}
