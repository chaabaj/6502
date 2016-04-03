cmake_minimum_required(VERSION 2.8)

project(test_arithmetic)

file(GLOB_RECURSE SRCS "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

if (UNIX OR APPLE)
    set(CMAKE_C_FLAGS "-ggdb -Wall")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

include_directories(include/ ../../include ../tools/include)

add_executable(test_arithmetic ${SRCS} ${HEADERS})

install(TARGETS test_arithmetic DESTINATION ../)

target_link_libraries(test_arithmetic spi_6502 spi_test_tools ${CMAKE_DL_LIBS})