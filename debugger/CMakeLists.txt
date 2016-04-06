cmake_minimum_required(VERSION 2.8)

project(6502_debugger)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

if (UNIX OR APPLE)
    set(CMAKE_CPP_FLAGS "-ggdb -std=c++14 -Wall")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

include_directories(include ../include)

add_executable(6502_debugger ${SRCS} ${HEADERS})

install(TARGETS 6502_debugger DESTINATION ../)

target_link_libraries(6502_debugger spi_6502)