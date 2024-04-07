# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
# Project name
project(water-management)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wunused-variable -Wpedantic")
set(CMAKE_CXX_STANDARD 17) # Enable C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++17 support by the compiler

add_definitions(-D_DARWIN_C_SOURCE -DNCURSES_WIDECHAR)

add_executable(water-management src/main.cpp
        src/BaseClasses/Reservoir.cpp
        src/BaseClasses/City.cpp
        src/BaseClasses/Pump.cpp
        src/GraphClasses/Vertex.cpp
        src/GraphClasses/Edge.cpp
        src/GraphClasses/Graph.cpp
        src/GraphClasses/StaticGraph.cpp
        src/BaseClasses/Pipe.cpp
        src/DataManagement/DataReader.cpp
        src/DataManagement/DataManager.cpp

        src/ui/components/Component.cpp
        src/ui/components/TextBox.cpp
        src/ui/components/TextLabel.cpp
        src/ui/components/InputBox.cpp
        src/ui/colors/ColorPair.cpp
        src/ui/colors/Color.cpp
        src/ui/components/SearchBox.cpp
        src/ui/components/OptionMenu.cpp
        src/ui/components/MultiComponent.cpp
        src/ui/menus/Buffer.cpp
        src/ui/menus/BasicMetricsBuffer.cpp
        src/ui/menus/BalanceBuffer.cpp
        src/ui/menus/MainBuffer.cpp
        src/ui/menus/ExportBuffer.cpp
        src/ui/menus/FailureBuffer.cpp)

# Check if the ncurses6.4 folder is present
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ncurses-6.4")
    message(STATUS "ncurses-6.4 folder found. Using existing installation.")
else()
    message(STATUS "Downloading ncurses-6.4.")
    file(DOWNLOAD https://ftp.gnu.org/gnu/ncurses/ncurses-6.4.tar.gz ${CMAKE_CURRENT_SOURCE_DIR}/ncurses.tar.gz)
    
    # Unpack
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/ncurses.tar.gz
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) 

    # Configure
    execute_process(COMMAND ./configure --enable-widec --enable-ext-colors WORKING_DIRECTORY 
        ${CMAKE_CURRENT_SOURCE_DIR}/ncurses-6.4 
        RESULT_VARIABLE build_result)

    if(NOT build_result EQUAL 0)
        execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/ncurses-6.4/)
        message(FATAL_ERROR "ncurses was not configured!")
    endif()

    # Make
    execute_process(COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ncurses-6.4 RESULT_VARIABLE build_result)
    if(NOT build_result EQUAL 0)
        execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/ncurses-6.4/)
        message(FATAL_ERROR "error ncurses make!")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_SOURCE_DIR}/ncurses.tar.gz)
endif()

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

target_link_libraries(water-management ${CMAKE_SOURCE_DIR}/ncurses-6.4/lib/libpanelw.a ${CMAKE_SOURCE_DIR}/ncurses-6.4/lib/libncursesw.a)

# Include any necessary header directories
target_include_directories(water-management PRIVATE
        src
        src/ui)