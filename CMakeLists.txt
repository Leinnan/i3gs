cmake_minimum_required(VERSION 2.8)

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "i3gs" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lconfig++")

## Set our project name
project(${PROJECT_NAME})



## Use all the *.cpp files we found under this folder for the project
FILE(GLOB SRCS "*.cpp" "*.c")

set(SOURCE_FILES
    Sources/Block.h
    Sources/Block.cpp
    main.cpp Sources/Manager.cpp Sources/Manager.h)

## Define the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
