echo off
set SCRIPTPATH=`readlink -f "$0"`
set PATH=`dirname "$SCRIPTPATH"`
mkdir -p result
git log --all > log.txt
# for now, pls compile test.cpp file as well
# we will comment this line b4 passing to TL
./test.exe 2018 Jan 1 2018 Dec 15
bash result/commit.cmd
g++ -std=c++11 DiffCnt.cpp -o DiffCnt.exe
./DiffCnt.exe 1 1 1 1 1
# move the .txt into the result folder
#rm test.exe