cmake_minimum_required(VERSION 3.13)
project(Driver)

set(CMAKE_CXX_STANDARD 14)

add_executable(Driver main.cpp gpio.cpp gpio.h Mux.cpp Mux.h)