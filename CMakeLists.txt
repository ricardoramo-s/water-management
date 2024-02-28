# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(water-management)

# Find ncurses
find_package(Curses REQUIRED)

# Create an executable target named "water-management"
add_executable(water-management src/main.cpp)

# Link ncurses library
target_link_libraries(water-management ${CURSES_LIBRARIES})

# Include ncurses headers
target_include_directories(water-management PRIVATE ${CURSES_INCLUDE_DIR})

# Include any necessary header directories
include_directories(src)
