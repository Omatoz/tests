# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(PT10 C)

set(CMAKE_C_STANDARD 99)

add_executable(PT10 main.c sousp1.c)

if(WIN32)
    target_link_libraries(PT10 kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
endif()
