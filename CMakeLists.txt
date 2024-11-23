cmake_minimum_required(VERSION 3.29)
project(ing1_quoridor_2024_groupe12_8 C)
# CMakeLists.txt

set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.10)
project(PT10 C)

include_directories("MAIN - main/sousp1/header")
set(CMAKE_C_STANDARD 99)

add_executable(ing1_quoridor_2024_groupe12_8
        "MAIN - main/header.h"
        "MAIN - main/main.c"
        "MAIN - main/sousp1.c")
add_executable(PT10 main.c sousp1.c)

if(WIN32)
    target_link_libraries(PT10 kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
endif()