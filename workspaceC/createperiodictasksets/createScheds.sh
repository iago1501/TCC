#!/bin/bash
 
#Digite a quantidade de tarefas que deseja criar, o nome padrão, e os valores de x, y e z respectivamente

seed=1180

if [ $# -eq 5 ]; 
then
 for i in $(seq -f "%03g" 1 $2)
 do   
#   echo $1-$i x=$3 y=$4 z=$5
 cd Release
  ./createperiodictasksets $1$i $3 $4 $5 $seed
 cd ..
  	
 let seed=seed+1
 done
  
else
  echo "ERROR: Precisa fornecer 5 argumentos:
        * o nome padrão
        * a quantidade de tarefas que deseja criar
        * os valores de x, y e z, respectivamente
 
    Ex: ./createScheds.sh filename 100 5 80 10
" 
  exit 1 
fi
