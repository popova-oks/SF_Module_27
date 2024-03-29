#include "../headers/Chat.h"
#include "../headers/Logger.h"
#include <fstream>
#include <iostream>
#include <limits>

Chat::Chat() : path_Clients_{"./clients.json"}, path_Messages_{"./log.json"} {}

void Chat::receive_message() {
    if(messages_ == nullptr) {
        messages_ = new Messages();
    }
    messages_->get_messages(this);
}

nlohmann::json Chat::update(nlohmann::json& json) {
    nlohmann::json answ_json;
    if(json["key"] == "1") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            answ_json["message"] = "The client is already exited!";
        } else {
            add_newClient(json);
            answ_json = list_observers();
        }
    } else if(json["key"] == "2") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            isAutorized(login);
            answ_json = list_observers();
        } else {
            answ_json["message"] = "This client isn't exist!";
        }
    } else if(json["key"] == "3") {
        std::string login = json["sender"];
        add_newMessage(json);
        answ_json = list_messages(login);
    } else if(json["key"] == "4") {
        std::string login = json["login"];
        answ_json = list_messages(login);
    } else if(json["key"] == "5") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            notAutorized(login);
            answ_json = list_observers();
        } else {
            answ_json["message"] = "This client isn't exist!";
        }
    } else if(json["key"] == "exit") {
        answ_json["message"] = "The server is closed!";
    }
    return answ_json;
}

void Chat::add_newClient(const nlohmann::json& json) {
    nlohmann::json dataUsers;
    Logger logger;
    if(logger.is_checkingFile(path_Clients_)) {
        dataUsers = logger.readFile(path_Clients_);
    } else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        dataUsers = nlohmann::json::array();
    }
    dataUsers.push_back(json);
    logger.writeFile(path_Clients_, dataUsers);
}

void Chat::add_newMessage(const nlohmann::json& json) {
    nlohmann::json dataMessages;
    Logger logger;
    if(logger.is_checkingFile(path_Messages_)) {
        dataMessages = logger.readFile(path_Messages_);
    } else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        dataMessages = nlohmann::json::array();
    }
    dataMessages.push_back(json);
    logger.writeFile(path_Messages_, dataMessages);
}

nlohmann::json Chat::list_observers() {
    nlohmann::json dataUsers;
    Logger logger;
    if(logger.is_checkingFile(path_Clients_)) {
        nlohmann::json json_data = logger.readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["isAutorized"] == true) {
                    dataUsers.push_back(json_data[i]);
                }
            }
        } else {
            dataUsers["message"] = "No users!";
        }
    }
    return dataUsers;
}

nlohmann::json Chat::list_messages(const std::string& login) {
    nlohmann::json dataMessages;
    Logger logger;
    if(logger.is_checkingFile(path_Messages_)) {
        nlohmann::json json_data = logger.readFile(path_Messages_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["receiver"] == login.c_str()) {
                    dataMessages.push_back(json_data[i]);
                }
            }
        } else {
            dataMessages["message"] = "No messages!";
        }
    }
    return dataMessages;
}

bool Chat::is_checkClient(const std::string& login, const std::string& password) {
    bool is_check = false;
    Logger logger;
    if(logger.is_checkingFile(path_Clients_)) {
        nlohmann::json json_data = logger.readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login && json_data[i]["password"] == password) {
                    is_check = true;
                    break;
                }
            }
        }
    }
    return is_check;
}

void Chat::isAutorized(const std::string& login) {
    nlohmann::json json_data;
    Logger logger;
    if(logger.is_checkingFile(path_Clients_)) {
        json_data = logger.readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login) {
                    json_data[i]["isAutorized"] = true;
                }
            }
        }
    }
    logger.writeFile(path_Clients_, json_data);
}

void Chat::notAutorized(const std::string& login) {
    nlohmann::json json_data;
    Logger logger;
    if(logger.is_checkingFile(path_Clients_)) {
        json_data = logger.readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login) {
                    json_data[i]["isAutorized"] = false;
                }
            }
        }
    }
    logger.writeFile(path_Clients_, json_data);
}