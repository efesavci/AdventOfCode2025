cmake_minimum_required(VERSION 3.16)
project(aoc2025 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB DAY_SOURCES "day[0-9][0-9].c")

# Create one executable per file
foreach(source ${DAY_SOURCES})
    get_filename_component(target ${source} NAME_WE)
    add_executable(${target} ${source})
endforeach()