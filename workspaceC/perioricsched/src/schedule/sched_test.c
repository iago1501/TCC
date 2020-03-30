#include "sched_test.h"
//___________________________________________________________________________________________________________
//Verifica se a saída é válida

int is_valid_exit(long *period, long *wcet, long *offset,  int num_tasks){

	int i;
	int position = 0;
	long t = 0;
	long total_lcm = period[0];

	if (num_tasks < 2){
		//printf("Verificação feita com êxito: Saída Válida\n\n");
		return 1;
	}

	task tasks[num_tasks];
	vet_to_taskvet(period, wcet, offset, num_tasks, tasks);
	sort_taskvet(tasks, num_tasks);
	
	
	GList *next_queue = taskvet_to_list(tasks, num_tasks);

	GList *l = NULL;
	task *x = next_queue->data;
	next_queue = g_list_remove(next_queue, next_queue->data);
	task *y = NULL;

	for(i = 1; i< num_tasks; i++){
		total_lcm = lcm(total_lcm, period[i]);
	}
	
	while(t < total_lcm){
	
		if(t > x->offset){
			//printf("Verificação feita com êxito: Saída Inválida\n\n");
			return 0;
		}		

		t = x->offset + x->wcet;
		x->offset = x->offset + x->period;

		//sort insert by offset		
		
		l = next_queue;
		position = 0;

		while(l != NULL){
			y = l->data;
			if(x->offset > y->offset){
				position++;
				l = g_list_next(l);
			}
			else{
				l = NULL;
			}		
		}


		next_queue = g_list_insert(next_queue, x, position);
		x = next_queue->data;	
		next_queue = g_list_remove(next_queue, next_queue->data);
	}	

	//printf("Verificação feita com êxito: Saída Válida\n\n");
	return 1;
		
}

