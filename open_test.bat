@echo off

rem set user=mazlan
rem set pwd=szmazozs2

rem setlocal ENABLEDELAYEDEXPANSION
rem set PATH=%PATH%;C:\cygwin\home\sandbox
rem endlocal

C:\cygwin\bin\bash --login -c "cd ../../../home; mkdir SEP_TA"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; mkdir Data"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone https://github.com/seemsus/sandbox"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git config --global credential.helper cache;"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_a/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_a
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_a
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git config --global credential.helper cache;"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_b/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_b
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_b
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_b; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_c/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_c
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_c
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_c; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_d/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_d
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_d
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_d; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_e/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_e
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_e
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_e; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_f/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_f
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_f
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_f; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_g/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_g
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_g
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_g; ./out.bat"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_h/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_h
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_h
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_h; ./out.bat"



pause
