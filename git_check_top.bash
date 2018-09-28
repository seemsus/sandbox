#!/bin/bash -f

mkdir result
git log --all > log.txt
g++ -c -o test.o test4.cpp -std=c++11
g++ -o test.exe test.o

cd ..
for i in sep250_18f_team_a sep250_18f_team_b sep250_18f_team_c sep250_18f_team_d sep250_18f_team_e sep250_18f_team_f sep250_18f_team_g sep250_18f_team_h
do
   echo "I am in directory: $i"
   pwd

#    ./test.exe 2018 Sep 26 2018 Sep 27
#    
#    mv ./name.txt    ./result/
#    mv ./commit.cmd  ./result
#    
#    source ./result/commit.cmd
done

