#!/bin/bash
 
#Digite a quantidade de tarefas que deseja criar, o nome padrão, e os valores de x, y e z respectivamente

if [ $# -eq 5 ]; 
then
 for i in $(seq -f "%03g" 1 $2)
 do
   saida=$1-$i-output   
   echo $1-$i x=$3 y=$4 z=$5 $saida 
 done
 
 
 
 
else
  echo "ERROR: Precisa fornecer 5 argumentos:
        * o nome padrão
        * a quantidade de tarefas que deseja criar
        * os valores de x, y e z, respectivamente
 
    Ex: ./createScheds.sh teste 5 7 8 10
" 
  exit 1 
fi
