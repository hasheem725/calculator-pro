cmake_minimum_required(VERSION 3.10)
project(CalculatorPro)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Create a library for the calculator logic
add_library(calc_lib src/calculator.cpp src/parser.cpp)

# Main Application
add_executable(calculator_app src/main.cpp)
target_link_libraries(calculator_app calc_lib)

# Unit Tests
add_executable(unit_tests tests/test_main.cpp)
target_link_libraries(unit_tests calc_lib)
