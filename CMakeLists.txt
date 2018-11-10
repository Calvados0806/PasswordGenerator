cmake_minimum_required(VERSION 3.5)

project(PasswordGenerator)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_SOURCE_DIR "${CMAKE_BINARY_DIR}/src")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(SOURCE_FILES
    src/mainwindow.cpp
    src/main.cpp
    src/mainwindow.h
    src/PassGen.hpp
    src/PassGen.cpp
    src/ThreadsManager.hpp
    src/ThreadsManager.cpp
    )

set(LINK_LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    )

if(UNIX)
    set(LINK_LIBS ${LINK_LIBS} pthread)
endif(UNIX)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
