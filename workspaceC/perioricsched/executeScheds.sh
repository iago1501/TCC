#!/bin/bash

echo Nome do Arquivo de Entrada: $1
echo Nome do Arquivo de Saída  : $2
echo Quantidade de Tasksets    : $3
echo Algoritmo a ser Executado : $4

#case 1: exhaustive_schedule_algoritm; 
#case 2: calculate_feasible_offsets_lp_bckt_2;
#case 3: hrst1_calculate_feasible_offsets_lp_bckt_2 (terá também que inserir o valor de K)
#case 4: calculate_feasible_offsets_lp_2;

k=$5

#filetimes=$1_algorithm$4k$k.txt 
#filetimes=$1_algorithm$4.txt 
filetimes=$2

#if [ $4 -eq 3 ]  
# then
#  echo Insira o valor de k:
#  read k
#fi

VALORESK=(-1 0 10 100 1000)

x=0

#echo Taskset \t| Time \t| >> $filetimes

#while [ $k -lt 5 ]; do
# filetimes=$1_algorithm$4_k${VALORESK[k]}.txt 
# echo Simplex $'\t' Feasible $'\t' Taskset $'\t' ExecTimeSec $'\t' ExecTimeMs $'\t' >> $filetimes
for i in $(seq -f "%03g" 1 $3) 
 do
  cd Debug
  start=$(date +"%T,%N")  
  ./perioricsched $1$i $2$i $4 $k ../$filetimes
  end=$(date +"%T,%N")
  cd ..
  startSec=`date +%s -d ${start}` 
  firstNs=`date +%N -d ${start}` 
  startNs=`expr $(( $startSec * 1000000000 )) + ${firstNs}`    
  endSec=`date +%s -d ${end}`
  lastNs=`date +%N -d ${end}` 
  endNs=`expr $(( $endSec * 1000000000 )) + ${lastNs}`    
  diffSec=`expr ${endSec} - ${startSec}`
  diffNs=`expr ${endNs} - ${startNs}`
  timeMs=`expr $(( $diffNs / 1000000 ))`    
  timesSec[$x]=$diffSec
  timesMs[$x]=$timeMs
  echo $'\t' $1$i $'\t' ${timesSec[x]}s $'\t' ${timesMs[x]}>> $filetimes	
  let x=$x+1
  echo End task $i $k
done
#  let k=$k+1
#done
