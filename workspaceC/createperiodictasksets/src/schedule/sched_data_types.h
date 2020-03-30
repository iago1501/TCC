#ifndef SCHED_DATA_TYPES_H

#define SCHED_DATA_TYPES_H

#include "sched_memory_init.h"
#include "sched_structs_defs.h"

//___________________________________________________________________________________________________________
//Recebe Vetores Retorna Lista


GList *vet_to_list(int *period, int *wcet, int *offset, int tam);

GList *taskvet_to_list(task *tasks, int tam);

void vet_to_taskvet(int *period, int *wcet, int *offset, int tam, task *tasks);

//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_vet(GList *l, int *period, int *wcet, int *offset);

//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_taskvet(GList *l, task *tasks);

//___________________________________________________________________________________________________________
//Retorna valores do vetor em uma lista

void get_tasklist_period(GList *l, int *period);
void get_tasklist_offset(GList *l, int *offset);
void get_tasklist_wcet(GList *l, int *wcet);

//___________________________________________________________________________________________________________
//Calcula Interseção de duas listas de offsets

void get_list_intersec(GList **listIntersec, GList *generated_offsets);

//___________________________________________________________________________________________________________
//Ordena vetor task de acordo com os valores de offset

void sort_taskvet(task *taskvet, int num_tasks);


#endif




