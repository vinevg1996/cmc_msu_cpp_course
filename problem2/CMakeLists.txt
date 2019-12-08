cmake_minimum_required(VERSION 3.5)
project(Taks2)

set(CMAKE_CXX_COMPILER "g++-7")
set (CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(factory_functions factory_functions.cpp factory_functions.h basic_function.cpp basic_function.h)

#add_executable(main main.cpp)

#target_link_libraries(main factory_functions)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main.cpp)

target_link_libraries(runTests factory_functions)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
