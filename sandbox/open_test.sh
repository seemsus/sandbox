echo off
DATA[0]="sep250_18f_team_a"
DATA[1]="sep250_18f_team_b"
DATA[2]="sep250_18f_team_c"
DATA[3]="sep250_18f_team_d"
DATA[4]="sep250_18f_team_e"
DATA[5]="sep250_18f_team_f"
DATA[6]="sep250_18f_team_g"
DATA[7]="sep250_18f_team_h"
for I in {0..1}
do
cd ..
rm -rf Result/${DATA[I]}_result/
cp sandbox/out.sh ${DATA[I]}/
cp sandbox/test.exe ${DATA[I]}/
cp sandbox/Diffcnt.exe ${DATA[I]}/
cd ${DATA[I]}
./out.sh
rm out.sh
rm test.exe
rm Diffcnt.exe
mv -f result ../Result/${DATA[I]}_result
done
sleep 5s