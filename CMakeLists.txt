cmake_minimum_required(VERSION 3.10)
project(water-management)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wunused-variable -Wpedantic")
set(CMAKE_CXX_STANDARD 17) # Enable C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++17 support by the compiler

add_executable(water-management
        src/main.cpp
        src/ui/components/Component.cpp
        src/ui/components/TextBox.cpp
        src/ui/components/Box.cpp
        src/ui/components/TextLabel.cpp
        src/ui/components/InputLabel.cpp
        src/ui/colors/ColorPair.cpp
        src/ui/colors/Color.cpp
        src/ui/components/SearchBox.cpp)

find_package(Curses REQUIRED)

target_link_libraries(water-management -lncurses)

target_include_directories(water-management PRIVATE
        ${CURSES_INCLUDE_DIR}
        src
        src/ui)