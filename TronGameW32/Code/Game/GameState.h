#pragma once
#include <SFML\Network.hpp>

enum GameState : sf::Int32
{
	GAME_OVER = 0,
	GAME_PAUSE = 1,
	GAME_START = 2,
	GAME_PLAY = 3,
	GAME_ROUND_OVER = 4
};