#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SV_PORT 7772
#define MESSAGE_LENGTH 1024

namespace TCP_Server {
    extern const char* server_addr;
    //extern struct sockaddr_in serveraddress, client;
    extern struct sockaddr_in serveraddress;
    
    extern socklen_t length;
    extern int socket_file_descriptor, bind_status, connection_status;

    int processRequest();
} // namespace TCP_Server
