#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"
#include <thread>

void Messages::get_messages(ISubject* chat) {
    // Communication Establishment
    TCP_Server::processRequest();
   
    while(true) {
        {
            struct sockaddr_in client;
            socklen_t length = sizeof(client);
            int connection = accept(TCP_Server::socket_file_descriptor,
                                    //(struct sockaddr*)&TCP_Server::client, &TCP_Server::length);
                                    (struct sockaddr*)&client, &length);
            if(connection == -1) {
                std::cout << "Server is unable to accept the data from client.!" << std::endl;
            } else {
                // создаем поток, который будет обрабатывать данные от клиента
                std::thread th1([this, chat, connection]() {
                    this->receive_message(chat, connection, std::ref(mtx));
                });
                // закрываем поток
                th1.join();
            }
        }
    }
    // закрываем сокет, завершаем соединение
    close(TCP_Server::socket_file_descriptor);
}

void Messages::receive_message(ISubject* chat, int connection, std::mutex& mtx) {
    char buff[1024];

    nlohmann::json json;
    nlohmann::json answ_json;

    // получаем сообщение от клиента
    ssize_t bytes = recv(connection, buff, sizeof(buff), 0);
    if(buff != nullptr) {
        if(bytes < 0) {
            answ_json["message"] = "Error receiving data from client!";
        } else if(bytes >= 0) {
            json = nlohmann::json::parse(buff);
            if(!json.is_null()) {
               std::lock_guard<std::mutex> lock(mtx);       // Использование мьютекса для записи в файл
                answ_json = chat->update(json);
            }
        }
        // отправляем ответ клиенту
        std::string answ_str_message;
        if(answ_json.is_null()) {
            answ_json["message"] = "No data from the server!";
        }
        answ_str_message = answ_json.dump();
        bytes = -1;
        bytes =
            send(connection, answ_str_message.c_str(), answ_str_message.size() + 1, 0);
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if(bytes >= 0) {
            std::cout << "Data successfully sent to the client!" << std::endl;
        } else {
            std::cout << "Data sending to the client failed!" << std::endl;
        }
    }
}