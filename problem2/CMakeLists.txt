cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_STANDARD 17)

add_library(factory_functions factory_functions.cpp factory_functions.h basic_function.cpp basic_function.h)

add_executable(main main.cpp)

target_link_libraries(main factory_functions)
