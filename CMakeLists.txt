cmake_minimum_required(VERSION 3.17)
project(queue)

set(CMAKE_CXX_STANDARD 17)

set(
    SOURCES
    queue.h
)

add_subdirectory(tests)

add_executable(queue main.cpp ${SOURCES})

add_library(libqueue STATIC ${SOURCES})
set_target_properties(libqueue PROPERTIES LINKER_LANGUAGE CXX)