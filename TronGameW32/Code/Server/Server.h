#pragma once

#include <Server/stdafx.h>
#include <SFML\Network.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <mutex>

#include "Client.h"
#include <Game\TronGame.h>

constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<Client>;

class Server
{
public:
	void runServer(); //Function to run server
	void runGame();	//Function to run game

private:
	void ping();
	bool bindServerPort();
	void clearStaleClients();
	void connect();
	void receivePacket();
	void processGamePacket(sf::Packet&, Client&);
	void listen();
	void sendGameData();

	//Networking variables
	TcpClients tcp_clients;
	sf::SocketSelector selector;
	sf::TcpListener listener;
	
	TronGame game;
	std::mutex mtx;
};