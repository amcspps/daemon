#!/bin/bash

cmake .

if [[ $? -eq 0 ]]
then
	make
fi

rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile compile_commands.json

echo "now start daemon using following instruction:"
echo "->sudo ./daemon </path/to/config>"
echo "->cfg path for test example is ./cfg.txt"
