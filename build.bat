@echo off

echo This script will compile EasyRP from source, for Windows. 
echo If you just want a precompiled exe go to the projects release page (https://github.com/Pizzabelly/EasyRP/releases)
echo Make sure you have both CMake and mingw32 installed and available in your PATH \r\n

echo Chocolatey: https://chocolatey.org/: 
echo choco install cmake git mingw  \r\n

echo Manual:
echo CMake - https://cmake.org/
echo git - https://git-scm.com/download/win
echo mingw32-make - http://www.mingw.org/ \r\n

echo press any key to continue building...

pause >nul

echo building discordapp/discord-rpc library
git clone https://github.com/discordapp/discord-rpc.git rpc
cd rpc
if not exist "build" mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_SH="CMAKE_SH-NOTFOUND"
mingw32-make SHELL=cmd
cd ../..
if not exist "lib" mkdir lib && cd lib
move ..\rpc\build\src\libdiscord-rpc.a .
cd ..
if not exist "include" mkdir include && cd include 
move ..\rpc\include\* .
cd ..

echo CMaking...
if not exist "build" mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_SH="CMAKE_SH-NOTFOUND"

echo compiling using mingw32-make/gcc..
mingw32-make SHELL=cmd

echo cleaning build artifacts...
cd ..
if not exist "EasyRP" mkdir EasyRP && cd EasyRP
move ..\build\EasyRP.exe .
copy ..\config.ini .
copy ..\README.md .
mkdir assets
