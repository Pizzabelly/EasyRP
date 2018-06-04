#!/bin/bash

echo "This script will compile EasyRP from the source (for linux/osx)"
echo "If you want a precompiled binary go here https://github.com/Pizzabelly/EasyRP/releases)"
echo "Build Dependencies are CMake, git, and probably your distro's build essentials"
read -p "Press any key to continue building..."


## Build discord-rpc library
echo "Building discord-rpc from its source"
git clone https://github.com/discordapp/discord-rpc.git discord-rpc
cd discord-rpc
mkidr -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make


## Build EasyRP
echo "Building EasyRP"
cd ../.. 
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make


## Make the package
cd ..
mkdir -p EasyRP
mv discord-rpc/build/src/libdiscord-rpc.a ./EasyRP/
mv build/EasyRP ./EasyRP/
cp config.ini ./EasyRP/
cp README.md ./EasyRP/
mkdir -p EasyRP/assets


