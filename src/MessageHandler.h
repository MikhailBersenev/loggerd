#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>

class MessageHandler {
public:
    MessageHandler();
    virtual ~MessageHandler();
    virtual void sendMessage(const std::string& message);

private:

};

#endif // MESSAGEHANDLER_H
