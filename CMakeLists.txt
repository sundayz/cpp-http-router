project(cpp-http-router)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

add_library(http-router STATIC src/router.cpp)

add_executable(http-router-test test/test.cpp)
target_link_libraries(http-router-test PUBLIC http-router)
