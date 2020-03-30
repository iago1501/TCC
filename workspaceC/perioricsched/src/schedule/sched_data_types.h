#ifndef SCHED_DATA_TYPES_H

#define SCHED_DATA_TYPES_H

#include "sched_memory_init.h"
#include "sched_structs_defs.h"

//___________________________________________________________________________________________________________
//Recebe Vetores Retorna Lista


GList *vet_to_list(long *period, long *wcet, long *offset, int tam);

GList *taskvet_to_list(task *tasks, int tam);

void vet_to_taskvet(long *period, long *wcet, long *offset, int tam, task *tasks);

//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_vet(GList *l, long *period, long *wcet, long *offset);

//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_taskvet(GList *l, task *tasks);

//___________________________________________________________________________________________________________
//Retorna valores do vetor em uma lista

void get_tasklist_period(GList *l, long *period);
void get_tasklist_offset(GList *l, long *offset);
void get_tasklist_wcet(GList *l, long *wcet);

//___________________________________________________________________________________________________________
//Calcula Interseção de duas listas de offsets

void get_list_intersec(GList **listIntersec, GList *generated_offsets);

//___________________________________________________________________________________________________________
//Ordena vetor task de acordo com os valores de offset

void sort_taskvet(task *taskvet, int num_tasks);


#endif




