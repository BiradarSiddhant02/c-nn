cmake_minimum_required(VERSION 3.0)
project(neural_network C)

include_directories(include)
file(GLOB SOURCES "src/*.c")

add_executable(neural_network main.c ${SOURCES})

set_target_properties(neural_network PROPERTIES C_STANDARD 99)
