#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

class Server {
public:
    explicit Server(int port);
    void start();

private:
    int port;
    int server_fd;
    sockaddr_in address;

    void setupSocket();
    void handleClient(int client_socket);
};

#endif
