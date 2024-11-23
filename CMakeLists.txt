# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ing1_quoridor_2024_groupe12_8 C)

set(CMAKE_C_STANDARD 99)

add_executable(ing1_quoridor_2024_groupe12_8 main.c sousp1.c)

if(WIN32)
    target_link_libraries(ing1_quoridor_2024_groupe12_8 kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
endif()
