@echo off

SET mypath=%~dp0
echo %mypath%

cd %mypath%
cd ..
rd /s /q build
mkdir build 
cd build

cmake ..
cmake --build .


