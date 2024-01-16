#pragma once
#include <map>
#include <mutex>
#include "ISubject.h"
#include "Logger.h"

class Messages {
  public:
    Messages() {}
    ~Messages(){};    
    void get_messages(ISubject* chat);  
    void receive_message(ISubject* chat, int connection, std::mutex &mtx);

  private:
    std::mutex mtx;
};