cmake_minimum_required(VERSION 3.10)
project(ConwaysGameOfLife)

set(CMAKE_CXX_STANDARD 17)


include_directories(src)


add_executable(game_of_life 
    src/main.cpp 
    src/Grid.cpp 
    src/Workflow.cpp
)