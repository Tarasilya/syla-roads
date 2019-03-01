#include <SFML/Network.hpp>

#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>

const int PORT = 44444;
const int PLAYERS = 2;

using namespace std;


int main() {
    sf::TcpListener listener;

    cerr << "trying to listen" << std::endl;
    if (listener.listen(PORT) != sf::Socket::Done)
    {
        std::cerr << "ERROR LISTENING TO PORT " << PORT << std::endl;
    }
    cerr << "listening to " << PORT << std::endl;

    std::vector<std::unique_ptr<sf::TcpSocket>> sockets (2);

    for (int i = 0; i < PLAYERS; i++) {
        std::cerr << "trying to accept " << i << std::endl;
        sockets[i] = std::make_unique<sf::TcpSocket>();
        sockets[i]->setBlocking(false);
        if (listener.accept(*sockets[i]) != sf::Socket::Done)
        {
            cerr << "ERROR ACCEPTING " << i << std::endl;
            exit(1);
        }

        std::cerr << "connection " << i << " accepted" << std::endl;
    }
    while(true) {
        for (int i = 0; i < PLAYERS; i++) {
            sf::Packet packet;
            if (sockets[i]->receive(packet) == sf::TcpSocket::Status::Done) {
                sockets[1-i]->send(packet);
                std::cerr << "vam posilka" << std::endl;
            }
        }
    }
}