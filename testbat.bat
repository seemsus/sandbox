:: Author : Hanzalah the Great II

REM Still in testing phase. Not fully completed. Will test out only for team a and b
REM Create a "sep250_18f_staff" folder if not created
REM Put "testbat.bat" + "test3.cpp" + "Makefile" in "sep250_18f_staff"
REM Clone "sep250_18f_team_a" and "sep250_18f_team_b" one level up of "sep250_18f_staff"
REM Create subfolders in "sep250_18f_staff" = "Results" and "Diff_outputs"
REM Create a dummy "log_a.txt" and "log_b.txt" in "Diff_outputs"
REM Run testbat.bat in "sep250_18f_staff"
REM Watch magic happens
REM Else call author

@echo off

REM To modify:
REM Do for all teams
REM Implement in for loops or
REM Implement Parallel execution
REM To note: Will work providing shell/environment has g++/make/diff build-in

ren %~dp0\Diff_outputs\log_a.txt log_old_a.txt 
ren %~dp0\Diff_outputs\log_b.txt log_old_a.txt

copy %~dp0\Makefile %~dp0\..\sep250_18f_team_a
copy %~dp0\Makefile %~dp0\..\sep250_18f_team_b

copy %~dp0\test3.cpp %~dp0\..\sep250_18f_team_a
copy %~dp0\test3.cpp %~dp0\..\sep250_18f_team_b

cd %~dp0\..\sep250_18f_team_a

make gcc0
move %~dp0\..\sep250_18f_team_a\log.txt %~dp0\Diff_outputs\log_a.txt
del commit.txt
del Makefile
del test3.cpp
del test.exe

cd %~dp0\..\sep250_18f_team_b

make gcc0
move %~dp0\..\sep250_18f_team_b\log.txt %~dp0\Diff_outputs\log_b.txt
del commit.txt
del Makefile
del test3.cpp
del test.exe

cd %~dp0\Diff_outputs

diff log_a.txt log_old_a.txt > team_a_res.txt
diff log_b.txt log_old_b.txt > team_b_res.txt

move %~dp0\Diff_outputs\team_a_res.txt %~dp0\Results\team_a_res.txt
move %~dp0\Diff_outputs\team_b_res.txt %~dp0\Results\team_b_res.txt

del log_old_a.txt
del log_old_b.txt

REM To add on:
REM Include timestamp for each results
REM Implement Grading.exe