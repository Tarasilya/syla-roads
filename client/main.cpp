#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
char* SERVER_NAME;
int SERVER_PORT;

int main() {
	// return 1;
	sf::TcpSocket socket;
	socket.setBlocking(false);
	sf::Socket::Status status = socket.connect(SERVER_NAME, SERVER_PORT);

	sf::Uint16 x = 27;
	std::string s = "Citizen";
	sf::Packet packet;
	packet << x << s;
	socket.send(packet);

}