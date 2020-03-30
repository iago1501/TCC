//Programa destinados a criar arquivos tasks XML

#include "schedule.h"
/*
//___________________________________________________________________________________________________________
//Recebe Valores

GList *get_values(int num_tasks){

	int i;
	int period, wcet;
	GList *list = NULL;

	for(i = 0; i < num_tasks; i++){
		printf("Digite o Period e o Wcet da Tarefa %d:\t", i+1);
		scanf("%d %d", &period, &wcet );
		list = g_list_append(list, set_task(period, wcet, 0));
	}

	return list;

}
*/
/*
//___________________________________________________________________________________________________________
//Algoritmo que cria tarefas com valores digitados

void create_file(){

	int num_tasks;
	char file[20];
	
	printf("Digite o nome do arquivo que deseja criar:\t");
	scanf("%s", file);

	printf("Digite a quantidade de tarefas que deseja:\t");
	scanf("%d", &num_tasks);


	GList *values_list = get_values(num_tasks);

	int period[g_list_length (values_list)];
	int wcet[g_list_length (values_list)];
	tasklist_to_vet(values_list, period, wcet, 0);

	create_xml(file, num_tasks, period, wcet);
}

*/

//___________________________________________________________________________________________________________
//Algoritmo que cria tarefas que são escalonáveis


GList *create_taskset(int x, int y, int z){

	int i, j, k;

	GList *offsets_intersec = NULL;
	GList *generated_offsets = NULL;
	
	task *task_w_chosen_offset;
	int *period;
	int ** gcds;

	GList *tasks_list = NULL;
	
	tasks_list = g_list_append(tasks_list,
	    		set_task(	(1 + (rand() % x)) * y, 1 + (rand() % z), 0	)	);

	//cria a primeira tarefa na lista de tarefas, uma tarefa é sempre escalonável

//	task_w_chosen_offset = g_list_first(tasks_list)->data;
	offsets_intersec = g_list_append(offsets_intersec, GINT_TO_POINTER(0));

	//armazena na variável task_w_chosen_offset a tarefa com o valor do offset escolhido
	//armazena na lista de interseção de offsets o valor de offsets para essa uma tarefa, que no caso é 0


	while(offsets_intersec != NULL){
	
		tasks_list = g_list_append(tasks_list,
				set_task(	(1 + (rand() % x)) * y, 1 + (rand() % z), 0)	);

		task *tasks_vet = (task*) malloc(g_list_length(tasks_list) * sizeof(task));
		tasklist_to_taskvet(tasks_list, tasks_vet);

		period = (int *) malloc (g_list_length(tasks_list) * sizeof(int));
		get_tasklist_period(tasks_list, period);

		gcds = allocate_gcds_matrix(g_list_length(tasks_list));
		init_gcds_matrix(gcds, g_list_length(tasks_list), period);

		for(j = 1; j < g_list_length(tasks_list); j++){
	
			i = 0;
			generated_offsets = NULL;
			offsets_intersec  = NULL;
			generate_offset(&generated_offsets, tasks_vet[i], tasks_vet[j], tasks_vet[i].offset, gcds[i][j], gcds[j][j]);

			offsets_intersec = generated_offsets;
			remove_equivalent_offset(&offsets_intersec, gcds[j][j]);

			for(i = 1; i < j; i++){
			
				generated_offsets = NULL;
				generate_offset(&generated_offsets, tasks_vet[i], tasks_vet[j], tasks_vet[i].offset, gcds[i][j], gcds[j][j]);
				get_list_intersec(&offsets_intersec, generated_offsets);
				g_list_free(generated_offsets);
				remove_equivalent_offset(&offsets_intersec, gcds[j][j]);

			}
		
			if(offsets_intersec != NULL){
				k = rand() % g_list_length(offsets_intersec);
				task_w_chosen_offset = g_list_last(tasks_list)->data;
				task_w_chosen_offset->offset = GPOINTER_TO_INT(g_list_nth(offsets_intersec, k)->data);
				g_list_last(tasks_list)->data = task_w_chosen_offset;
			}
	
		}
		
		free(period);
		free(tasks_vet);
		free(gcds);
	}

	return tasks_list;
}


//___________________________________________________________________________________________________________
//Programa Principal


int main(int argc, char *argv[]){


	if(argc < 6){
		printf("Parâmetros de entrada insuficientes, digite o nome do arquivo que deseja criar, o valor de x, y e z");
		exit(1);
	}

	char *input_file_name = argv[1];
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	int z = atoi(argv[4]);
	int seed = atoi(argv[5]);

	time_t t;
	GList *non_scheduled_tasks = NULL;
	GList *scheduled_tasks = NULL;

	srand(seed);

	non_scheduled_tasks = create_taskset(x,y,z);
	
//CRIAÇÃO DO ARQUIVO DE TAREFAS NÃO ESCALONÁVEIS

	int non_scheduled_list_size = g_list_length(non_scheduled_tasks);
	int non_scheduled_periods[non_scheduled_list_size];
	int non_scheduled_wcets[non_scheduled_list_size];
	get_tasklist_period(non_scheduled_tasks, non_scheduled_periods);
	get_tasklist_wcet(non_scheduled_tasks, non_scheduled_wcets);
	non_scheduled_wcets[non_scheduled_list_size-1] = non_scheduled_periods[non_scheduled_list_size-1];

	char *non_scheduled_text = "non_scheduled_";

	char *non_scheduled_file_name= (char *) malloc(1 + strlen(input_file_name)+ strlen(non_scheduled_text) );
	strcpy(non_scheduled_file_name, non_scheduled_text);
	strcat(non_scheduled_file_name, input_file_name);

	create_xml(non_scheduled_file_name, non_scheduled_list_size, non_scheduled_periods, non_scheduled_wcets);

//CRIAÇÃO DO ARQUIVO DE TAREFAS ESCALONÁVEIS

	scheduled_tasks = g_list_remove(non_scheduled_tasks, g_list_last(non_scheduled_tasks)->data);
	
	int scheduled_list_size = g_list_length(scheduled_tasks);
	int scheduled_periods[scheduled_list_size];
	int scheduled_wcets[scheduled_list_size];
	int scheduled_offsets[scheduled_list_size];
	get_tasklist_period(scheduled_tasks, scheduled_periods);
	get_tasklist_wcet(scheduled_tasks, scheduled_wcets);
	get_tasklist_offset(scheduled_tasks, scheduled_offsets);

	char *scheduled_text = "scheduled_";

	char *scheduled_file_name= (char *) malloc(1 + strlen(input_file_name)+ strlen(scheduled_text) );
	strcpy(scheduled_file_name, scheduled_text);
	strcat(scheduled_file_name, input_file_name);


	create_xml(scheduled_file_name, scheduled_list_size, scheduled_periods, scheduled_wcets);

	//FIM

	printf("\n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	printf("            Conjunto de Tarefas Escalonáveis         \n\n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	print_list(scheduled_tasks);
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
	printf("Conjunto criado com sucesso\n");
	printf("\n");	
	print_vector(scheduled_offsets, scheduled_list_size);




	return 0;
}
