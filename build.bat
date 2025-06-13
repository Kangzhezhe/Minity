@echo off
if not exist build (
    mkdir build
)
cd build

cmake .. -G "MinGW Makefiles"
if errorlevel 1 exit /b

mingw32-make -j16
if errorlevel 1 exit /b

cd ../bin
if errorlevel 1 exit /b

SandBox.exe
pause