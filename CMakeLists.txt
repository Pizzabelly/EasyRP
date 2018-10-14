cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 99)
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

project(EasyRP)

# discord-rpc subproject
set(ENABLE_IO_THREAD OFF CACHE INTERNAL "disable io thread for discord-rpc" FORCE) 
set(BUILD_EXAMPLES OFF CACHE INTERNAL "don't build examples for discord-rpc" FORCE) 
add_subdirectory(discord-rpc)

include_directories(discord-rpc/include)
add_executable(EasyRP src/discord.c src/parser.c src/main.c res/EasyRP.rc)

target_link_libraries(EasyRP LINK_PUBLIC discord-rpc)
