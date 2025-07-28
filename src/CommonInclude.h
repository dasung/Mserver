#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class MarketDataServer {
public:
    void sendMarketData(const std::string& data, const std::vector<int>& clients, std::mutex& client_mutex) {
        std::lock_guard<std::mutex> lock(client_mutex);
        for (int client : clients) {
            send(client, data.c_str(), data.size(), 0);
        }
    }
};

class OrderBook {
private:
    std::mutex book_mutex;
    std::unordered_map<int, double> orders;
public:
    void addOrder(int orderID, double price) {}
    void removeOrder(int orderID) {}
    void getSnapshot() {}
    void getDelta() {}
};

class TCPServer {
private:
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    std::vector<int> clients;
    std::mutex client_mutex;
    MarketDataServer marketDataServer;

public:
    TCPServer(int port) {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            perror("Socket failed");
            exit(EXIT_FAILURE);
        }
        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 10) < 0) {
            perror("Listen failed");
            exit(EXIT_FAILURE);
        }
    }

    void acceptClients() {
        while (true) {
            int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                perror("Accept failed");
                continue;
            }
            
            std::lock_guard<std::mutex> lock(client_mutex);
            clients.push_back(new_socket);
            std::thread(&TCPServer::handleClient, this, new_socket).detach();
        }
    }

    void handleClient(int client_socket) {
        char buffer[1024] = {0};
        while (true) {
            int valread = read(client_socket, buffer, 1024);
            if (valread <= 0) {
                close(client_socket);
                return;
            }
            std::cout << "Received: " << buffer << std::endl;
        }
    }

    void broadcastMarketData(const std::string& data) {
        marketDataServer.sendMarketData(data, clients, client_mutex);
    }

    ~TCPServer() {
        close(server_fd);
        for (int client : clients) {
            close(client);
        }
    }
};