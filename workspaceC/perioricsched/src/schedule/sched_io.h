#ifndef SCHED_IO_H

#define SCHED_IO_H

#include "sched_memory_init.h"



//___________________________________________________________________________________________________________
//Criação de um XML teste


void create_xml(char *file, int numTasks, long *caughtPeriods, long *caughtWcets);

//___________________________________________________________________________________________________________
//Escreve XML saida



void write_xml(char *file, int numTasks, long *periods, long *wcets, long *offsets);

//___________________________________________________________________________________________________________
//Leitura do XML...recebe arquivo e joga para Lista


GList *read_xml(char *file, GList *list);

//___________________________________________________________________________________________________________
//Printa Lista

void print_list(GList *l);

void print_list_int(GList *l);

//___________________________________________________________________________________________________________
//Printa Vetor

void print_vector(long *vector, int size);

void print_tasks_vector(task *vector, int size);

//___________________________________________________________________________________________________________
//Printa Matriz

void print_matrix(long **matrix, int size);



#endif
