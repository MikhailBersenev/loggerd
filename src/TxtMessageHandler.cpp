#include "TxtMessageHandler.h"

TxtMessageHandler::TxtMessageHandler(const std::string& filePath)
    : m_output(filePath, std::ios::app) {
}

TxtMessageHandler::~TxtMessageHandler() {
    if (m_output.is_open()) {
        m_output.close();
    }
}

void TxtMessageHandler::sendMessage(const std::string& message) {
    if (m_output.is_open()) {
        m_output << message << std::endl;
    }
}
