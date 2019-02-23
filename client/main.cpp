#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
char* SERVER_NAME;
int SERVER_PORT;

int main() {
	return 1;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(SERVER_NAME, SERVER_PORT);
}