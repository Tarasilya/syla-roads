#pragma once

#include <SFML/Network.hpp>

class Client{
	sf::TcpSocket socket;

	Client();

	void Send(sf::Keyboard::Key key);
	
	std::vector<sf::Keyboard::Key> Receive();
};