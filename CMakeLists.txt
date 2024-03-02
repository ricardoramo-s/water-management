cmake_minimum_required(VERSION 3.10)
project(water-management)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wunused-variable -Wpedantic")
set(CMAKE_CXX_STANDARD 17) # Enable C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++17 support by the compiler

add_executable(water-management
        src/main.cpp
        src/ui/Component.cpp
        src/ui/TextBox.cpp
        src/ui/Box.cpp
        src/ui/TextLabel.cpp
        src/ui/InputLabel.cpp
        src/ui/InputLabel.h
        src/ui/KeysBindings.h)

find_package(Curses REQUIRED)

target_link_libraries(water-management -lncurses)

target_include_directories(water-management PRIVATE
        ${CURSES_INCLUDE_DIR}
        src)