#include "sched_data_types.h"

//___________________________________________________________________________________________________________
//Recebe Vetores Retorna Lista


GList *vet_to_list(long *period, long *wcet, long *offset, int tam){

	int i;
	GList *list = NULL;

	for(i = 0; i < tam; i++){

	list = g_list_append(list,
	    		set_task(period[i], wcet[i], offset[i]));
	}

	return list;

}

GList *taskvet_to_list(task *tasks, int tam){

	int i;

	GList *list = NULL;
	
	
	for(i = 0; i < tam; i++){
	
		list = g_list_append(list, 
				set_task(tasks[i].period, tasks[i].wcet, tasks[i].offset));
	
	}


	return list;

}


void vet_to_taskvet(long *period, long *wcet, long *offset, int tam, task *tasks){

	int i;
		
	for(i = 0; i < tam; i++){

		tasks[i].wcet 	= wcet[i];
		tasks[i].period = period[i];
		tasks[i].offset	= offset[i];		
		
	}

}
//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_vet(GList *l, long *period, long *wcet, long *offset){

	int i = 0;
	task *content;

	while (l != NULL){

		content = l->data;

		period[i] = content->period;
		wcet[i] = content->wcet;
		offset[i] = content->offset;

		i++;
	    l = g_list_next(l);


	}
}

//___________________________________________________________________________________________________________
//Recebe Lista Retorna Vetores


void tasklist_to_taskvet(GList *l, task *tasks){

	int i = 0;

	while (l != NULL){

		task *content = l->data;

		tasks[i].period = content->period;
		tasks[i].wcet 	= content->wcet;
		tasks[i].offset	= content->offset;
		i++;
		l = g_list_next(l);

	}
}

//___________________________________________________________________________________________________________
//Retorna valores do vetor em uma lista

void get_tasklist_period(GList *l, long *period){
	
	int i = 0;
	task *content;

	while (l != NULL){

		content = l->data;

		period[i]= content->period;
		i ++;
		l = g_list_next(l);
	}
	
}


void get_tasklist_offset(GList *l, long *offset){
	
	int i = 0;
	task *content;

	while (l != NULL){
	
		content = l->data;

		offset[i]= content->offset;
		i ++;
		l = g_list_next(l);
	}
	
}

void get_tasklist_wcet(GList *l, long *wcet){
	
	int i = 0;
	task *content;

	while (l != NULL){
	
		content = l->data;

		wcet[i]= content->wcet;
		i ++;
		l = g_list_next(l);
	}
	
}

//___________________________________________________________________________________________________________
//Calcula Interseção de duas listas de offsets

void get_list_intersec(GList **list_intersec, GList *generated_offsets){

	GList *intersec = *list_intersec;
	GList *aux = generated_offsets;

	*list_intersec = NULL;
	long offset1, offset2;

	while(intersec != NULL){
		offset1 = GPOINTER_TO_INT(intersec->data);
		while(aux != NULL){
			offset2 = GPOINTER_TO_INT(aux->data);
			if(offset1 == offset2){
				*list_intersec = g_list_append(*list_intersec, aux->data);
				break;
			}
			aux = g_list_next(aux);
		}
		aux = generated_offsets;
		intersec = g_list_remove(intersec, intersec->data);
	}
}


//___________________________________________________________________________________________________________
//Ordena vetor task de acordo com os valores de offset

void sort_taskvet(task *taskvet, int num_tasks){

	int i, j;
	task aux;

	for(i = 0; i < (num_tasks - 1); i++){
		for(j = i + 1; j < num_tasks; j++){
			if(taskvet[i].offset > taskvet[j].offset){

				aux = taskvet[j];
				taskvet[j] = taskvet[i];
				taskvet[i] = aux;
			
			}
		} 
	}
}
