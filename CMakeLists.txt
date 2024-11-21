cmake_minimum_required(VERSION 3.29)
project(ing1_quoridor_2024_groupe12_8 C)

set(CMAKE_C_STANDARD 11)

include_directories("MAIN - main/sousp1/header")

add_executable(ing1_quoridor_2024_groupe12_8
    "MAIN - main/sousp1/header/header.h"
    "MAIN - main/sousp1/header/main.c"
    "MAIN - main/sousp1/header/sousp1.c")
