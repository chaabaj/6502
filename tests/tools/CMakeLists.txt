cmake_minimum_required(VERSION 2.6)

project(spi_6502)

file(GLOB_RECURSE SRCS "*src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

if (UNIX OR APPLE)
    add_definitions("-Wall -ggdb")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)

include_directories(include)

add_library(spi_test_tools SHARED ${SRCS} ${HEADERS})

TARGET_LINK_LIBRARIES(spi_test_tools)