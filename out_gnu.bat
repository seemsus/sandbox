
@ echo off

setlocal
set PATH=%PATH%;%~dp0
set /a num=0

call mkdir result
call git log --all > log.txt
call g++ -c -o test.o test3.cpp -std=c++11
call g++ -o test.exe test.o
call test.exe 2018 Jan 10 2018 Jan 15
call commit.cmd

rem setlocal ENABLEDELAYEDEXPANSION
rem for /F "tokens=*" %%x in (commit.txt) do (
rem   rem git diff %%x >> batfile!num!.txt
rem   git %%x
rem   set /a num=num+1
rem )
rem endlocal

del /Q /S *.exe
del /Q /S *.cmd
del /Q /S *.txt
rem del /Q %~dp0\result
rem call rmdir /Q %~dp0\result

rem pause


