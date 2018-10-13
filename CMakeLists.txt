cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 99)
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

project(EasyRP)

set(ENABLE_IO_THREAD OFF CACHE INTERNAL "disable io thread for discord-rpc" FORCE) 
add_subdirectory(./discord-rpc)

LINK_DIRECTORIES(.)
include_directories(discord-rpc/include)
add_executable(EasyRP src/discord.c src/parser.c src/main.c res/EasyRP.rc)

IF (WIN32)
    target_link_libraries(EasyRP LINK_PUBLIC discord-rpc.lib pthread)
ELSE()
    target_link_libraries(EasyRP LINK_PUBLIC libdiscord-rpc.a pthread)
ENDIF()
