@echo off

rem setlocal ENABLEDELAYEDEXPANSION
rem set PATH=%PATH%;C:\cygwin\home\sandbox
rem endlocal
set /a num=0

C:\cygwin\bin\bash --login -c "cd ../../../home; mkdir SEP_TA"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; mkdir Data"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone https://github.com/seemsus/sandbox"

rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git config --global credential.helper cache;"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA/sandbox; g++ -c -o test.o test4.cpp -std=c++11;"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA/sandbox; g++ -c -o diff.o DiffCnt.cpp -std=c++11;"
copy C:\cygwin\home\SEP_TA\sandbox\open_test_bat.bat C:\cygwin\home\SEP_TA\sandbox
copy C:\cygwin\home\SEP_TA\sandbox\diff.o C:\cygwin\home\SEP_TA\Data

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA/sandbox; ./open_test_bat.bat" 

copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_a
copy C:\cygwin\home\SEP_TA\sandbox\test.o C:\cygwin\home\SEP_TA\sep250_18f_team_a
copy C:\cygwin\home\SEP_TA\sandbox\diff.o C:\cygwin\home\SEP_TA\sep250_18f_team_a
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a; ./out.bat"
copy C:\cygwin\home\SEP_TA\sandbox\diff.o C:\cygwin\home\SEP_TA\sep250_18f_team_a\result
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a/result; g++ -o diff.exe diff.o"
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a/result; ./diff.exe"
move C:\cygwin\home\SEP_TA\sep250_18f_team_a\result C:\cygwin\home\SEP_TA\Data
ren C:\cygwin\home\SEP_TA\Data\result result%num%

set /a num=num+1

echo %num%

pause
