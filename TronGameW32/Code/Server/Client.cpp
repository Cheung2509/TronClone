#include "Client.h"
#include <Game\PacketType.h>

Client::Client(sf::TcpSocket* sock) : 
	socket(sock)
{

}

Client::Client(Client && rhs)
{
	this->id = rhs.id;
	this->latency = rhs.latency;
	this->socket = std::move(rhs.socket);
}

sf::TcpSocket & Client::getSocket()
{
	return *socket;
}

void Client::setLatency(std::chrono::microseconds duration)
{
	latency = duration;
}

Client & Client::operator=(Client && rhs)
{
	this->id = rhs.id;
	this->latency = rhs.latency;
	this->socket = std::move(rhs.socket);
	return *this;
}

bool Client::isConected() const
{
	return socket->getLocalPort() != 0;
}

void Client::ping()
{
	sf::Packet ping;
	ping << PacketType::PING;
	getSocket().send(ping);

	timestamp = std::chrono::steady_clock::now();
}

void Client::pong()
{
	auto end = std::chrono::steady_clock::now();
	latency = std::chrono::duration_cast
		<std::chrono::microseconds>
		(end - timestamp);

	latency /= 2;
}

unsigned int Client::next_id = 0;