cmake_minimum_required (VERSION 3.8)

project ("daemon")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable (daemon "main.cpp" "daemon.cpp")
