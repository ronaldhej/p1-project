cmake_minimum_required(VERSION 3.23)
project(p_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(
        p_1 src/main.c
        src/graph/graph.c
        src/graph/graph.h
        src/utility/utility.c
        src/utility/utility.h
        src/pathfinding/pathfinding.c
        src/pathfinding/pathfinding.h
)