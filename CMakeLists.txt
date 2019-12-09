cmake_minimum_required(VERSION 3.15)
project(start)

include_directories(x86_64-w64-mingw32/include/SDL2
        )

set(CMAKE_CXX_STANDARD 14)


add_executable(start main.cpp)
find_library(SDL2 C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/bin)

target_link_libraries(start -lSDL2 -lSDL2_image)
