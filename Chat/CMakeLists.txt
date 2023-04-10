# CMakeList.txt: проект CMake для Chat; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Chat "main.cpp" "Chat.h" "User.h" "Chat.cpp" "User.cpp" "Message.h" "Message.cpp" "Sha1.h" "Sha1.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
