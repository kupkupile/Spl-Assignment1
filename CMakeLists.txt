cmake_minimum_required(VERSION 3.12)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp src/Restaurant.cpp src/Dish.cpp src/Customer.cpp src/Table.cpp)