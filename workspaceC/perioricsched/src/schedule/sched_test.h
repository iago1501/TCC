#ifndef SCHED_TEST_H
#define SCHED_TEST_H

#include "sched_data_types.h"

//___________________________________________________________________________________________________________
//Verifica se a saída é válida

int is_valid_exit(long *period, long *wcet, long *offset, int num_tasks);

#endif
