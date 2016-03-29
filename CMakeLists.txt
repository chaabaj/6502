cmake_minimum_required(VERSION 2.8)

project(emulator)

file(GLOB_RECURSE SRCS "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

if (UNIX OR APPLE)
    set(CMAKE_C_FLAGS "-O3 -Wall")
endif()

include_directories(include)

add_executable(6502 ${SRCS} ${HEADERS})

install(TARGETS 6502 DESTINATION ../bin)

target_link_libraries (6502 ${CMAKE_DL_LIBS})
