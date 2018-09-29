#!/bin/bash -f

mkdir result
git log --all > log.txt
g++ -c -o test.o test4.cpp -std=c++11
g++ -o test.exe test.o

cd ..
for i in sep250_18f_team_*
do
   echo
   echo "///////////////////////////////////////////////////////////////////////////////"
   echo "// Processing for : $i"
   echo "///////////////////////////////////////////////////////////////////////////////"
   cd $i
   echo "Entering the processing directory..."
   pwd
   echo "Leaving the processing directory..."
   cd ..

#    ./test.exe 2018 Sep 26 2018 Sep 27
#    
#    mv ./name.txt    ./result/
#    mv ./commit.cmd  ./result
#    
#    source ./result/commit.cmd
done

