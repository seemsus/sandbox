#!/bin/bash -f

mkdir result
git log --all > log.txt
g++ -c -o test.o test4.cpp -std=c++11
g++ -o test.exe test.o
./test.exe 2018 Sep 26 2018 Sep 27

mv ./name.txt    ./result/
mv ./commit.cmd  ./result
#call %~dp0\result\commit.cmd

source ./result/commit.cmd