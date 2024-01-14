#include "../headers/ConnectionTCP.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace TCP_Client {
    char buff[MESSAGE_LENGTH];
    int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
    const char* server_addr = "127.0.0.1"; 

    int processMessage() {
        // Создадим сокет
        socket_file_descriptor = socket(
            AF_INET, SOCK_STREAM, 0); // SOCK_STREAM указывает на создание соксета для потоковой
                                      // передачи данных, что соответствует протоколу TCP.
        if(socket_file_descriptor == -1) {
            std::cout << "Creation of Socket failed!" << std::endl;
            exit(1);
        }

        // Установим адрес сервера
        if(inet_pton(AF_INET, server_addr, &serveraddress.sin_addr.s_addr) <= 0) {
            std::cout << "Invalid address/ Address not supported" << std::endl;
            exit(1);
        }

        // Зададим номер порта
        serveraddress.sin_port = htons(CL_PORT);
        // Используем IPv4
        serveraddress.sin_family = AF_INET;
        // Установим соединение с сервером
        connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress,
                             sizeof(serveraddress));
        if(connection == -1) {
            std::cout << "Connection with the server failed!" << std::endl;
            exit(1);
        }
        return connection;
    }
} // namespace TCP_Client


