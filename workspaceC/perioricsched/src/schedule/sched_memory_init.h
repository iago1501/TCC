#ifndef SCHED_MEMORY_INIT_H

#define SCHED_MEMORY_INIT_H

#include "sched_structs_defs.h"

//___________________________________________________________________________________________________________
//Aloca uma estrutura do tipo Task

task *set_task(long period, long wcet, long offset);

//___________________________________________________________________________________________________________
//Faz alocação de uma matrix do tipo long


void allocate_gcds_matrix(long ***gcds, int num_tasks);

void allocate_n_matrix(int ***n, int num_tasks);

//___________________________________________________________________________________________________________
//Euclid's algorithm

long gcd(long a, long b);

long lcm(long a, long b);

//___________________________________________________________________________________________________________
//Matriz espelho GCD

void init_gcds_matrix(long **gcds, int num_tasks, long *periods);

#endif

