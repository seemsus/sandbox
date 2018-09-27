
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

if exist %~dp0\result (
  cd /d %~dp0
  for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
)

cd /d %~dp0\..\
del /Q sandbox
rem del /Q /S test.exe
rem del /Q /S commit.cmd
rem del /Q /S log.txt
rem del /Q %~dp0\result
rem call rmdir /Q %~dp0\result

rem pause


