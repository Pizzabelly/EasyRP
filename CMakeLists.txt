cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(EasyRP)
LINK_DIRECTORIES(./lib)

add_executable(EasyRP config.cpp config.hpp discord.cpp discord.hpp main.cpp EasyRP.rc)

target_link_libraries(EasyRP LINK_PUBLIC libdiscord-rpc.a pthread)

