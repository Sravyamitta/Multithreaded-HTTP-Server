#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include "ThreadPool.h"

class Server {
public:
    explicit Server(int port);
    void start();

private:
    int port;
    int server_fd;
    sockaddr_in address;

    ThreadPool pool;

    void setupSocket();
    void handleClient(int client_socket);
};

#endif
