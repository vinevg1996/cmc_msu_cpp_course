cmake_minimum_required(VERSION 3.5)
project(my_iterator)

set(CMAKE_CXX_COMPILER "g++-7")
set (CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(my_iterator my_iterator.cpp my_iterator.h)

#add_executable(main main.cpp)

#target_link_libraries(main factory_functions)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main.cpp)

target_link_libraries(runTests my_iterator)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
