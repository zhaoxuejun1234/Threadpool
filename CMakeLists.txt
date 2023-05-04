cmake_minimum_required(VERSION 3.25)
project(My_Threadpool)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(My_Threadpool
        main.cpp
        Task.cpp
        Task.h
        threadpool.cpp
        threadpool.h)
find_package(Threads REQUIRED)
target_link_libraries(My_Threadpool Threads::Threads)
