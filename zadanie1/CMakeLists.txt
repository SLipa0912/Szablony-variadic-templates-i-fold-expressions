cmake_minimum_required(VERSION 3.14)
project(zadanie1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(zadanie1 main.cpp)

if(MSVC)
    target_compile_options(zadanie1 PRIVATE /W4)
else()
    target_compile_options(zadanie1 PRIVATE -Wall -Wextra -pedantic)
endif()