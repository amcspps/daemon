cmake_minimum_required (VERSION 3.8)

project ("daemon")
set(CMAKE_BUILD_TYPE Debug)

add_executable (daemon "main.cpp" "daemon.cpp")
