#include "Server.h"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

Server::Server(int port) : port(port), server_fd(-1) {}

void Server::setupSocket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << std::endl;
}

void Server::handleClient(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, World!";

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

void Server::start() {
    setupSocket();

    while (true) {
        socklen_t addrlen = sizeof(address);

        int client_socket = accept(
            server_fd,
            (struct sockaddr*)&address,
            &addrlen
        );

        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        handleClient(client_socket);
    }
}
