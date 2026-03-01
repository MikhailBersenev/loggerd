#ifndef TXTMESSAGEHANDLER_H
#define TXTMESSAGEHANDLER_H

#include <fstream>
#include <string>

#include "MessageHandler.h"

class TxtMessageHandler : public MessageHandler {
public:
    explicit TxtMessageHandler(const std::string& filePath);
    ~TxtMessageHandler() override;
    void sendMessage(const std::string& message) override;

private:
    std::ofstream m_output;
};

#endif // TXTMESSAGEHANDLER_H
