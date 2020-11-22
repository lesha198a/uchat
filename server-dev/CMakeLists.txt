cmake_minimum_required(VERSION 3.10)


set(CMAKE_C_COMPILER clang)
project(uchat_server)
add_executable(uchat_server src/main.c inc/server.h)
set_property(TARGET uchat_server PROPERTY C_STANDARD 11)