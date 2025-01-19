#!/usr/bin/bash

if [ ! -d "Debug/" ]
then
    mkdir Debug/
    cd Debug/
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cd ../
fi

cmake --build Debug/ &&
cd Debug/bin &&
./tedit CMakeLists.txt &&
cd ../../ &&
cp Debug/compile_commands.json .