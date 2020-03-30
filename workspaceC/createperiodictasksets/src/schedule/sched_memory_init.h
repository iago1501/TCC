#ifndef SCHED_MEMORY_INIT_H

#define SCHED_MEMORY_INIT_H

#include "sched_structs_defs.h"

//___________________________________________________________________________________________________________
//Aloca uma estrutura do tipo Task

task *set_task(int period, int wcet, int offset);

//___________________________________________________________________________________________________________
//Faz alocação de uma matrix do tipo int


int ** allocate_gcds_matrix(int num_tasks);

void allocate_n_matrix(int ***n, int num_tasks);

//___________________________________________________________________________________________________________
//Euclid's algorithm

int gcd(int a, int b);

int lcm(int a, int b);

//___________________________________________________________________________________________________________
//Matriz espelho GCD

void init_gcds_matrix(int **gcds, int num_tasks, int *periods);

#endif

