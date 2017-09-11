#pragma once
#include <SFML\Network.hpp>
#include <Game\Direction.h>
#include <Game\TronGame.h>

#include <mutex>

const sf::IpAddress SERVER_IP("127.0.0.1");
constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

class NetworkClient
{
public:
	NetworkClient() = default;
	~NetworkClient() = default;

	//Getters
	int getID() const;

	void runClient(TronGame*);
	bool connect();
	bool isConnected();
	const void sendInput(Direction&);
	void processGamePacket(sf::Packet&);
private:
	sf::TcpSocket socket;
	int id;
	TronGame* game = nullptr;
	std::mutex mtx;
};