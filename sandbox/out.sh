echo off
set SCRIPTPATH=`readlink -f "$0"`
set PATH=`dirname "$SCRIPTPATH"`
mkdir -p result
git log --all --date=local > log.txt
# for now, pls compile test.cpp file as well
# we will comment this line b4 passing to TL
./test.exe 2018 Jan 1 2018 Dec 15
cd result/
./commit.cmd
cd ..
#g++ -std=c++11 DiffCnt.cpp -o DiffCnt.exe
# code comment space new deleted (whole numbers)
./DiffCnt.exe 1 1 1 1 1
mv log.txt result/
#rm test.exe