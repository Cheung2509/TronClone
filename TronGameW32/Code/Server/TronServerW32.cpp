// TronServerW32.cpp : Defines the entry point for the console application.
//
#include <Server/stdafx.h>
#include <SFML\Network.hpp>
#include <iostream>

#include "Server.h"

int main()
{
	Server server;

	while (true)
	{
		server.runServer();
	}
	return 0;
}