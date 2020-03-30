#!/bin/bash

cut -d" " -f6 non_scheduled_taskset1_1.txt > algoritmo1_output.txt
cut -d" " -f6 non_scheduled_taskset1_k0.txt > algoritmo3k0_output.txt
cut -d" " -f6 non_scheduled_taskset1_k-1.txt > algoritmo3k-1_output.txt

cut -d" " -f6 periodx2_non_scheduled_taskset1_1.txt > periodx2_algoritmo1_output.txt
cut -d" " -f6 periodx2_non_scheduled_taskset1_k0.txt > periodx2_algoritmo3k0_output.txt
cut -d" " -f6 periodx2_non_scheduled_taskset1_k-1.txt > periodx2_algoritmo3k-1_output.txt

cut -d" " -f6 periodx3_non_scheduled_taskset1_1.txt > periodx3_algoritmo1_output.txt
cut -d" " -f6 periodx3_non_scheduled_taskset1_k0.txt > periodx3_algoritmo3k0_output.txt
cut -d" " -f6 periodx3_non_scheduled_taskset1_k-1.txt > periodx3_algoritmo3k-1_output.txt

cut -d" " -f6 periodx4_non_scheduled_taskset1_1.txt > periodx4_algoritmo1_output.txt
cut -d" " -f6 periodx4_non_scheduled_taskset1_k0.txt > periodx4_algoritmo3k0_output.txt
cut -d" " -f6 periodx4_non_scheduled_taskset1_k-1.txt > periodx4_algoritmo3k-1_output.txt

paste algoritmo1_output.txt periodx2_algoritmo1_output.txt periodx3_algoritmo1_output.txt periodx4_algoritmo1_output.txt algoritmo3k0_output.txt periodx2_algoritmo3k0_output.txt periodx3_algoritmo3k0_output.txt periodx4_algoritmo3k0_output.txt algoritmo3k-1_output.txt periodx2_algoritmo3k-1_output.txt periodx3_algoritmo3k-1_output.txt periodx4_algoritmo3k-1_output.txt experiment2_1sttasksets_exectime.txt



