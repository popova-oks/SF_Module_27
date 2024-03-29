#include "../headers/ConnectionTCP.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace TCP_Server {
    const char* server_addr;
    
    //struct sockaddr_in serveraddress, client;
    struct sockaddr_in serveraddress;

    //socklen_t length;
    int socket_file_descriptor, bind_status, connection_status;

    int processRequest() {
        // Системный вызов, который создает новый соксет и возвращает его дескриптор.
        socket_file_descriptor = socket(
            AF_INET, SOCK_STREAM, 0); // SOCK_STREAM указывает на создание соксета для потоковой
                                      // передачи данных, что соответствует протоколу TCP.
        if(socket_file_descriptor == -1) {
            std::cout << "Socket creation failed!" << std::endl;
            exit(1);
        }
        // Устанавливаем IP-адрес сервера в структуре
        serveraddress.sin_addr.s_addr =
            htonl(INADDR_ANY); // "INADDR_ANY" означает, что сервер будет прослушивать все доступные
                               // сетевые интерфейсы на хосте.
        // Зададим номер порта для связи
        serveraddress.sin_port = htons(SV_PORT);
        // Используем IPv4
        serveraddress.sin_family = AF_INET;

        // Привяжем сокет
        bind_status =
            bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));

        // Проверяем результат
        if(bind_status == -1) {
            std::cout << "Socket binding failed!" << std::endl;
            exit(1);
        }

        // Происходит установка серверного соксета в режим прослушивания (listening) для входящих
        // соединений listen() - это функция соксета, которая используется для уведомления
        // операционной системы, что серверный соксет готов принимать входящие соединения от
        // клиентов
        connection_status = listen(socket_file_descriptor, 1);
        // Проверяем результат
        if(connection_status == -1) {
            std::cout << "Socket is unable to listen for new connections.!" << std::endl;
            exit(1);
        } else {
            std::cout << "Server is listening for new connection: " << std::endl;
        }
        //length = sizeof(client);
        return socket_file_descriptor;
    };

} // namespace TCP_Server
