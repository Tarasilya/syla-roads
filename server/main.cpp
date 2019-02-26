#include <SFML/Network.hpp>

#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

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
    socket.setBlocking(false);
    if (listener.accept(socket) != sf::Socket::Done)
    {
        // error...
    }
    cerr << "connection accepted" << std::endl;

    // while(true) {
    //     sf::Packet packet;
    //     socket.receive(packet);
    //     std::string x;
    //     packet >> x;
    //     std::cout << x << std::endl;
    // }
    mutex m;

    std::thread t1 ([&]
    {
        std::string s;
        while(true) {
            getline(cin, s);
            m.lock();
            sf::Packet packet;
            packet << s;
            socket.send(packet);
            m.unlock();
        }
    });
    std::thread t2 ([&]
    {
        std::string s;
        while(true) {
            m.lock();
            sf::Packet packet;
            if (socket.receive(packet) == sf::TcpSocket::Status::Done) {
                packet >> s;
                std::cout << "(" << s << ")" << std::endl;
            }
            m.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    t1.join();
    t2.join();  
}