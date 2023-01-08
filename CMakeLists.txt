cmake_minimum_required(VERSION 3.23)
project(AED2)

set(CMAKE_CXX_STANDARD 14)

add_executable(AED2 main.cpp Graph.cpp Graph.h Airport.h Airport.cpp Airline.cpp Airline.h hashTable.cpp)
