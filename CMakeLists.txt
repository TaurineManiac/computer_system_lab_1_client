cmake_minimum_required(VERSION 3.20)
project(client)

set(CMAKE_CXX_STANDARD 20)

# Создаем исполняемый файл

add_executable(client mainClient.cpp)
# Указываем путь к заголовочным файлам
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR})

# Импортируем первую DLL (inputCheck)
add_library(InputCheck SHARED IMPORTED)
set_target_properties(InputCheck PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libinputCheck.dll"
        IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/libinputCheck.dll.a"
)

# Импортируем вторую DLL (megagenerate)
add_library(megagenerate SHARED IMPORTED)
set_target_properties(megagenerate PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libmegagenerate.dll"
        IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/libmegagenerate.dll.a"
)

# Линкуем библиотеку
target_link_libraries(client  PRIVATE ws2_32 InputCheck megagenerate)

