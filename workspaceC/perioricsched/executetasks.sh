#!/bin/bash

nice -20 ./executeScheds.sh non_scheduled_experiment1_1sttasksets non_scheduled_taskset1_1 101 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_1sttasksets non_scheduled_taskset1_k0 101 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_1sttasksets non_scheduled_taskset1_k-1 101 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_2ndttasksets non_scheduled_taskset2_1 101 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_2ndttasksets non_scheduled_taskset2_k0 101 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_2ndttasksets non_scheduled_taskset2_k-1 101 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_3rdttasksets non_scheduled_taskset3_1 100 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_3rdttasksets non_scheduled_taskset3_k0 100 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_3rdttasksets non_scheduled_taskset3_k-1 100 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_4thttasksets non_scheduled_taskset4_1 102 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_4thttasksets non_scheduled_taskset4_k0 102 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_4thttasksets non_scheduled_taskset4_k-1 102 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_5thttasksets non_scheduled_taskset5_1 100 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_5thttasksets non_scheduled_taskset5_k0 100 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_5thttasksets non_scheduled_taskset5_k-1 100 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_6thttasksets non_scheduled_taskset6_1 102 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_6thttasksets non_scheduled_taskset6_k0 102 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_6thttasksets non_scheduled_taskset6_k-1 102 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_7thttasksets non_scheduled_taskset7_1 100 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_7thttasksets non_scheduled_taskset7_k0 100 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_7thttasksets non_scheduled_taskset7_k-1 100 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_8thttasksets non_scheduled_taskset8_1 100 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_8thttasksets non_scheduled_taskset8_k0 100 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_8thttasksets non_scheduled_taskset8_k-1 100 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_9thttasksets non_scheduled_taskset9_1 101 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_9thttasksets non_scheduled_taskset9_k0 101 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_9thttasksets non_scheduled_taskset9_k-1 101 3 -1

nice -20 ./executeScheds.sh non_scheduled_experiment1_10thttasksets non_scheduled_taskset10_1 100 1 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_10thttasksets non_scheduled_taskset10_k0 100 3 0
nice -20 ./executeScheds.sh non_scheduled_experiment1_10thttasksets non_scheduled_taskset10_k-1 100 3 -1

cd experimento1

cut -d" " -f6 non_scheduled_taskset1_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset1_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset1_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset1_exectime.txt

cd ..

cd experimento2

cut -d" " -f6 non_scheduled_taskset2_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset2_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset2_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset2_exectime.txt

cd ..

cd experimento3

cut -d" " -f6 non_scheduled_taskset3_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset3_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset3_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset3_exectime.txt

cd ..

cd experimento4

cut -d" " -f6 non_scheduled_taskset4_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset4_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset4_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset4_exectime.txt

cd ..

cd experimento5

cut -d" " -f6 non_scheduled_taskset5_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset5_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset5_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset5_exectime.txt

cd ..


cd experimento6

cut -d" " -f6 non_scheduled_taskset6_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset6_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset6_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset6_exectime.txt

cd ..

cd experimento7

cut -d" " -f6 non_scheduled_taskset7_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset7_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset7_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset7_exectime.txt

cd ..

cd experimento8

cut -d" " -f6 non_scheduled_taskset8_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset8_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset8_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset8_exectime.txt

cd ..

cd experimento9

cut -d" " -f6 non_scheduled_taskset9_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset9_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset9_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset9_exectime.txt

cd ..

cd experimento10

cut -d" " -f6 non_scheduled_taskset10_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset10_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset10_k-1.txt > algoritmo3k-1_output.txt

paste algoritmo1_output.txt algoritmo3k0_output.txt algoritmo3k-1_output.txt experiment1_taskset10_exectime.txt

cd ..


nice -20 ./executeScheds.sh periodx2non_scheduled_experiment1_1sttasksets periodx2_non_scheduled_taskset1_1 101 1 0
nice -20 ./executeScheds.sh periodx2non_scheduled_experiment1_1sttasksets periodx2_non_scheduled_taskset1_k0 101 3 0
nice -20 ./executeScheds.sh periodx2non_scheduled_experiment1_1sttasksets periodx2_non_scheduled_taskset1_k-1 101 3 -1

nice -20 ./executeScheds.sh periodx3non_scheduled_experiment1_1sttasksets periodx3_non_scheduled_taskset1_1 101 1 0
nice -20 ./executeScheds.sh periodx3non_scheduled_experiment1_1sttasksets periodx3_non_scheduled_taskset1_k0 101 3 0
nice -20 ./executeScheds.sh periodx3non_scheduled_experiment1_1sttasksets periodx3_non_scheduled_taskset1_k-1 101 3 -1

nice -20 ./executeScheds.sh periodx4non_scheduled_experiment1_1sttasksets periodx4_non_scheduled_taskset1_1 101 1 0
nice -20 ./executeScheds.sh periodx4non_scheduled_experiment1_1sttasksets periodx4_non_scheduled_taskset1_k0 101 3 0
nice -20 ./executeScheds.sh periodx4non_scheduled_experiment1_1sttasksets periodx4_non_scheduled_taskset1_k-1 101 3 -1
