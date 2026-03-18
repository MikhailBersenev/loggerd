#include "Loggerd.h"
#include "MessageHandler.h"
#include "TxtMessageHandler.h"

int main()
{
    Loggerd* logger = Loggerd::getInstance();

    MessageHandler consoleHandler;
    TxtMessageHandler fileHandler("exampleApp.log");

    logger->addMessageHandler(&consoleHandler);
    logger->addMessageHandler(&fileHandler);

    LOG_DEBUG_MSG("Приложение запущено");
    LOG_INFO_MSG("Инициализация завершена");
    LOG_TRACE_MSG("Контрольная точка trace");
    LOG_CRITICAL_MSG("Пример критического сообщения");

    return 0;
}
