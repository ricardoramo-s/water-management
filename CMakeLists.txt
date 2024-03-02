# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(water-management)

# Find ncurses
find_package(Curses REQUIRED)

# Create an executable target named "water-management"
add_executable(water-management src/main.cpp
        src/Reservoir.h)

# Link ncurses library
target_link_libraries(water-management ${CURSES_LIBRARIES})

# Include ncurses headers
target_include_directories(water-management PRIVATE ${CURSES_INCLUDE_DIR})

# Include any necessary header directories
include_directories(src)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
