cmake_minimum_required(VERSION 3.27)
project(tecnicas_proyecto C)

set(CMAKE_C_STANDARD 11)

add_executable(tecnicas_proyecto main.c
        Models/structl.c
        Models/structl.h
)
