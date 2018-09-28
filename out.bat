
@ echo off

setlocal
set PATH=%PATH%;%~dp0
set /a num=0

call mkdir result
call git log --all > log.txt
rem call g++ -c -o test.o test3.cpp -std=c++11
call g++ -o test.exe test.o
call test.exe 2018 Jan 10 2018 Jan 15
move %~dp0\name.txt %~dp0\result
move %~dp0\commit.cmd %~dp0\result
call %~dp0\result\commit.cmd

rem setlocal ENABLEDELAYEDEXPANSION
rem for /F "tokens=*" %%x in (commit.txt) do (
rem   rem git diff %%x >> batfile!num!.txt
rem   git %%x
rem   set /a num=num+1
rem )
rem endlocal

rem deleting everything in the folder 
rem if exist %~dp0\result (
rem   cd /d %~dp0
rem   for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
rem )

rem cd /d %~dp0\..\
rem del /Q sandbox

rem timeout /t 5
rem if [%errorlevel%]==[1] echo failed
rem if [%errorlevel%]==[0] echo successful

rem C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/sandbox; ./out_gnu.bat"

del /Q /S test.exe
del /Q /S commit.cmd
del /Q /S log.txt

move %~dp0\result %~dp0\..\..\

del /Q %~dp0\result
call rmdir /Q %~dp0\result

rem pause


