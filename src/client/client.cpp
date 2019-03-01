#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "game/game_config.h"
#include "client.h"

using namespace std;

sf::Packet& operator <<(sf::Packet& packet, sf::Keyboard::Key& key){
    packet << (int) key;
    return packet;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Keyboard::Key& key){
    int key_index;
    packet >> key_index;
    key = (sf::Keyboard::Key) key_index;
    return packet;
}

Client::Client(){
    GameConfig& config = GameConfig::getInstance();


    std::string server_name = config.GetString("server_name");
    int server_port = config.GetInt("server_port");
    // get server_name and server_port

    socket.setBlocking(false);
    sf::Socket::Status status = socket.connect(server_name.c_str(), server_port);
}

std::vector<sf::Keyboard::Key> Client::Receive(){
    std::vector<sf::Keyboard::Key> keys;
    sf::Packet packet;
    while (socket.receive(packet) == sf::TcpSocket::Status::Done){
        std::cout << "received" << "\n";
        sf::Keyboard::Key key;
        packet >> key;
        keys.push_back(key);
    }
    return keys;
}

void Client::Send(sf::Keyboard::Key key){
    sf::Packet packet;
    packet << key;
    socket.send(packet);
}

// int main() {
// 	// return 1;
// 	sf::TcpSocket socket;
//     socket.setBlocking(false);
//     sf::Socket::Status status = socket.connect(SERVER_NAME, SERVER_PORT);

//     mutex m;

//     std::thread t1 ([&]
//     {
//         std::string s;
//         while(true) {
//             getline(cin, s);
//             m.lock();
//             sf::Packet packet;
//             packet << s;
//             socket.send(packet);
//             m.unlock();
//         }
//     });
//     std::thread t2 ([&]
//     {
//         std::string s;
//         while(true) {
//             m.lock();
//             sf::Packet packet;
//             if (socket.receive(packet) == sf::TcpSocket::Status::Done) {
//                 packet >> s;
//                 std::cout << "(" << s << ")" << std::endl;
//             }
//             m.unlock();
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//         }
//     });
//     t1.join();
//     t2.join();	
	
// }