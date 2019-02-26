#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <SFML/Network.hpp>

using namespace std;
char* SERVER_NAME = "localhost";
int SERVER_PORT = 44444;

int main() {
	// return 1;
	sf::TcpSocket socket;
    socket.setBlocking(false);
    sf::Socket::Status status = socket.connect(SERVER_NAME, SERVER_PORT);

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