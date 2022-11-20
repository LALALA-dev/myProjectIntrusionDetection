#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <thread>
#define portNum 54000


class server{
    public:
    static void setupConnection();
    static void serverListening(int clientSocket);
};