#include <SFML/Network.hpp>

#include <string>
#include <iostream>

const int PORT = 44444;


using namespace std;

int main() {
    sf::TcpListener listener;

    cerr << "trying to listen" << std::endl;
    if (listener.listen(PORT) != sf::Socket::Done)
    {
        // error...
    }
    cerr << "listening to " << PORT << std::endl;

    cerr << "trying to accept..." << std::endl;
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done)
    {
        // error...
    }
    cerr << "connection accepted" << std::endl;

    while(true) {
        sf::Packet packet;
        socket.receive(packet);
        std::string x;
        packet >> x;
        std::cout << x << std::endl;
    }
}