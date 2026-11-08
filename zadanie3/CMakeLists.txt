cmake_minimum_required(VERSION 3.14)
project(zadanie3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(zadanie3 main.cpp)

if(MSVC)
    target_compile_options(zadanie3 PRIVATE /W4)
else()
    target_compile_options(zadanie3 PRIVATE -Wall -Wextra -pedantic)
endif()