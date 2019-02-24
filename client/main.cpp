#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
char* SERVER_NAME;
int SERVER_PORT = 44444;

int main() {
	// return 1;
	sf::TcpSocket socket;
	socket.setBlocking(false);
	sf::Socket::Status status = socket.connect(SERVER_NAME, SERVER_PORT);

	std::string s;
	while(true){
		std::cin >> s;
		sf::Packet packet;
		packet << s;
		socket.send(packet);
	}
	
}