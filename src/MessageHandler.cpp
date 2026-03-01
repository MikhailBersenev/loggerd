#include "MessageHandler.h"

#include <iostream>

MessageHandler::MessageHandler() {

}

MessageHandler::~MessageHandler() {

}

void MessageHandler::sendMessage(const std::string& message)
{
    std::cout << message << std::endl;
}
