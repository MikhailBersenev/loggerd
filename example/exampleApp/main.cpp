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

    LOG_DEBUG_MSG(LOG_MAIN, "Приложение запущено");
    LOG_INFO_MSG(LOG_MAIN, "Инициализация завершена");
    LOG_TRACE_MSG(LOG_MAIN, "Контрольная точка trace");
    LOG_CRITICAL_MSG(LOG_MAIN, "Пример критического сообщения");

    return 0;
}
