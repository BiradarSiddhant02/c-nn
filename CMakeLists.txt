cmake_minimum_required(VERSION 3.0)
project(neural_network C)

include_directories(include)
file(GLOB SOURCES "src/*.c")

# Find all files in the include directory
file(GLOB INCLUDE_FILES "include/*")

# Print the names of all files in the include directory
foreach(file ${INCLUDE_FILES})
    message(STATUS "Include file: ${file}")
endforeach()

add_executable(neural_network main.c ${SOURCES})

set_target_properties(neural_network PROPERTIES C_STANDARD 99)
