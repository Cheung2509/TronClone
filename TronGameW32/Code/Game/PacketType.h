#pragma once
#include <SFML/Network.hpp>

enum PacketType : sf::Int32
{
	INVALID = 0,
	GAME = 1,
	PING = 2,
	PONG = 3,
	ASSIGN_ID = 4,
};