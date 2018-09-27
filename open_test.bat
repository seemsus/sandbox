@echo off

rem set user=mazlan
rem set pwd=szmazozs2

rem setlocal ENABLEDELAYEDEXPANSION
rem set PATH=%PATH%;C:\cygwin\home\sandbox
rem endlocal

rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone https://github.com/seemsus/sandbox"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_a"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_b"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_c"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_d"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_e"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_f"
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://%user%:%pwd%@git.sg.digipen.edu/projects/sep250_18f_team_g"

C:\cygwin\bin\bash --login -c "cd ../../../home; mkdir SEP_TA"
C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone https://github.com/seemsus/sandbox"

C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_a/;"
copy C:\cygwin\home\SEP_TA\sandbox\out.bat C:\cygwin\home\SEP_TA\sep250_18f_team_a
copy C:\cygwin\home\SEP_TA\sandbox\test3.cpp C:\cygwin\home\SEP_TA\sep250_18f_team_a
timeout /t 5
C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/SEP_TA/sep250_18f_team_a; ./out.bat"

rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_b/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_c/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_d/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_e/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_f/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_g/;"
rem 
rem C:\cygwin\bin\bash --login -c "cd ../../../home/SEP_TA; git clone http://git.sg.digipen.edu/projects/sep250_18f_team_h/;"
rem timeout /t 5
rem if [%errorlevel%]==[1] echo failed
rem if [%errorlevel%]==[0] echo successful

rem C:\cygwin\bin\bash --login -c "cd C:/cygwin/home/sandbox; ./out_gnu.bat"

pause
