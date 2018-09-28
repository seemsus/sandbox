@echo off

rem setlocal ENABLEDELAYEDEXPANSION
rem set PATH=%PATH%;C:\cygwin\home\sandbox
rem endlocal

C:\cygwin\bin\bash --login -c "cd ../../../home; mkdir SEP_TA"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; mkdir Data"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone https://github.com/seemsus/sandbox"

rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git config --global credential.helper cache;"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA/sandbox; g++ -c -o test.o test4.cpp -std=c++11;"
copy C:\cygwin\home\sandbox\open_test_bat.bat C:\cygwin\home\SEP_TA\sandbox

pause

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA/sandbox; ./open_test_bat.bat" 

pause

copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_a
copy C:\cygwin\home\SEP_TA\sandbox\test.o C:\cygwin\home\SEP_TA\sep250_18f_team_a
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a; ./out.bat"

pause
