project(tests)

add_subdirectory(googletest)

add_executable(tests queue.cpp)
target_link_libraries(tests gtest gtest_main libqueue)