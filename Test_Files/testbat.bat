REM Author : Hanzalah the Great II

:: Still in testing phase. Not fully completed. Will test out only for team a and b
:: Create a "sep250_18f_staff" folder if not created
:: Put "testbat.bat" + "test3.cpp" in "sep250_18f_staff"
:: Create subfolders in "sep250_18f_staff" = "Results" and "Diff_outputs"
:: Create a dummy "log_a.txt" and "log_b.txt" in "Diff_outputs"
:: Run testbat.bat in "sep250_18f_staff"
:: Watch magic happens
:: Else call author

:: To modify:
:: Do for all teams
:: Implement in for loops or
:: Implement Parallel execution
:: To note: Will work providing shell/environment has g++/make/diff/git build-in

cd %~dp0\..\

:: uncomment below if you want it as prompt
::set /p user= "Enter git username: "   
::set /p pwd= "Enter git password: "

set user=m.mazlan
set pwd=szmazozs2

git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_a 
git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_b 

ren %~dp0\Diff_outputs\log_a.txt log_old_a.txt 
ren %~dp0\Diff_outputs\log_b.txt log_old_a.txt

copy %~dp0\test3.cpp %~dp0\..\sep250_18f_team_a
copy %~dp0\test3.cpp %~dp0\..\sep250_18f_team_b

cd %~dp0\..\sep250_18f_team_a

call git log --all > log.txt
call g++ -c -o test.o test3.cpp -std=c++11
call g++ -o test.exe test.o
call test.exe 2018 Jan 10 2018 Jan 15
call commit.cmd
move %~dp0\..\sep250_18f_team_a\log.txt %~dp0\Diff_outputs\log_a.txt
del test3.cpp
del test.exe

cd %~dp0\..\sep250_18f_team_b

call git log --all > log.txt
call g++ -c -o test.o test3.cpp -std=c++11
call g++ -o test.exe test.o
call test.exe 2018 Jan 10 2018 Jan 15
call commit.cmd
move %~dp0\..\sep250_18f_team_b\log.txt %~dp0\Diff_outputs\log_b.txt
del test3.cpp
del test.exe

cd %~dp0\Diff_outputs

diff log_a.txt log_old_a.txt > team_a_res.txt
diff log_b.txt log_old_b.txt > team_b_res.txt

move %~dp0\Diff_outputs\team_a_res.txt %~dp0\Results\team_a_res.txt
move %~dp0\Diff_outputs\team_b_res.txt %~dp0\Results\team_b_res.txt

del log_old_a.txt
del log_old_b.txt

:: continue to grading.exe