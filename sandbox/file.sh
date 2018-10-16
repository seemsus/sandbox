echo off
cd ..
ls > sandbox/ls.txt
declare -i CNT=-1
declare -i VAL=0
while read line; do
  DATA[VAL]=$line
  CNT+=1
  VAL+=1
done < sandbox/ls.txt
for I in `seq 2 $CNT`
do
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
  cd ..
done
rm sandbox/ls.txt