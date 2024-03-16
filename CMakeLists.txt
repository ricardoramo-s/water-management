cmake_minimum_required(VERSION 3.10)
project(water-management)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wunused-variable -Wpedantic")
set(CMAKE_CXX_STANDARD 17) # Enable C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++17 support by the compiler

add_definitions(-D_DARWIN_C_SOURCE -DNCURSES_WIDECHAR)

add_executable(water-management
        src/main.cpp
        src/ui/components/Component.cpp
        src/ui/components/TextBox.cpp
        src/ui/components/TextLabel.cpp
        src/ui/components/InputBox.cpp
        src/ui/colors/ColorPair.cpp
        src/ui/colors/Color.cpp
        src/ui/components/SearchBox.cpp
        src/ui/components/OptionMenu.cpp
        src/ui/components/MultiComponent.cpp
        src/ui/menus/Menu.cpp
        src/ui/menus/ReservoirMenu.cpp
        src/ui/components/Cmdline.cpp)

find_package(Curses REQUIRED)
target_link_libraries(water-management -lncurses -lpanel)

target_include_directories(water-management PRIVATE
        /usr/local/include/ncursesw
        /usr/local/include
        src
        src/ui)