cmake_minimum_required(VERSION 3.16)

project(exampleApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# В рекомендуемой схеме `config.h` принадлежит приложению.
# Перед сборкой loggerd сообщаем его расположение.
set(LOGGERD_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Directory containing config.h for loggerd" FORCE)

# Подключаем библиотеку loggerd из корня репозитория (loggerd/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. loggerd_build)

add_executable(exampleApp main.cpp)

# Привязываем библиотеку к исполняемому файлу
target_link_libraries(exampleApp PRIVATE loggerd::loggerd)

# Указываем правила установки
include(GNUInstallDirs)
install(TARGETS exampleApp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
