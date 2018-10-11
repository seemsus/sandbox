
@ echo off

setlocal
set PATH=%PATH%;%~dp0
set /a num=0

call mkdir result
call git log --all > log.txt
call g++ -c -o test.o test4.cpp -std=c++11
call g++ -o test.exe test.o
call test.exe 2018 Sep 26 2018 Sep 27
move %~dp0\name.txt %~dp0\result
move %~dp0\commit.cmd %~dp0\result
call %~dp0\result\commit.cmd

rem call jarren function:


rem del /Q /S test.exe
rem del /Q /S commit.cmd
rem del /Q /S log.txt
rem del /Q %~dp0\result
rem call rmdir /Q %~dp0\result

pause

rem test codes:
rem setlocal ENABLEDELAYEDEXPANSION
rem for /F "tokens=*" %%x in (commit.txt) do (
rem   rem git diff %%x >> batfile!num!.txt
rem   git %%x
rem   set /a num=num+1
rem )
rem endlocal

rem if exist %~dp0\result (
rem   cd /d %~dp0\result
rem   for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
rem )
rem 
rem cd /d %~dp0\..\
rem del /Q sandbox

rem timeout /t 5
rem if [%errorlevel%]==[1] echo failed
rem if [%errorlevel%]==[0] echo successful

rem C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/sandbox; ./out_gnu.bat"




