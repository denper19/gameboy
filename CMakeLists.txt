cmake_minimum_required(VERSION 3.21)

project(gb1)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
    "cpu.hpp"
    "cpu.cpp"
    "main.cpp"
)

add_executable(gb1 ${PROJECT_SOURCES})

enable_testing()

add_executable(
  cpu_tests
  test_cpu.cpp
)
target_link_libraries(
  cpu_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cpu_tests)