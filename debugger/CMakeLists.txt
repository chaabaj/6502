cmake_minimum_required(VERSION 2.8)

project(6502_debugger)

file(GLOB_RECURSE SRCS "src/*.c")

if (UNIX OR APPLE)
    set(CMAKE_C_FLAGS "-ggdb -Wall")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

include_directories(../include)

add_executable(6502_debugger ${SRCS} ${HEADERS})

install(TARGETS 6502_debugger DESTINATION ../)

target_link_libraries(6502_debugger spi_6502)