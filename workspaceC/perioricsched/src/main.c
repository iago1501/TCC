#include "schedule.h"

int glp_simplex_count = 0;
//___________________________________________________________________________________________________________
//Programa Principal


int main(int argc, char *argv[]){

	/*
	 Escolha de algoritmos:
	  case 1: exhaustive_schedule_algoritm;
	  case 2: calculate_feasible_offsets_lp_bckt_2;
	  case 3: hrst1_calculate_feasible_offsets_lp_bckt_2;
	  case 4: calculate_feasible_offsets_lp_2;
*/

	if(argc != 6){
		printf("Parâmetros de entrada insuficientes, digite o nome do arquivo de entrada e saída e o número do algoritmo que irá executar \n ");
		printf("Escolha de algoritmos: \n case 1: exhaustive_schedule_algoritm; \n case 2: calculate_feasible_offsets_lp_bckt_2; \n case 3: hrst1_calculate_feasible_offsets_lp_bckt_2; \n case 4: calculate_feasible_offsets_lp_2;");
		exit(1);
	}

	GList *list = NULL;

	//long **gcds;

	long num_tasks;

	char *input_file_name = argv[1];
	char *output_file_name = argv[2];
	char *filetimes = argv[5];
	int algoritmo  = atoi(argv[3]);
	int k;

	if(algoritmo == 3){
		k = atoi(argv[4]);
	}

/*
	printf("-----------------------------------------------------\n\n");
	printf("              Passando de XML Para Lista             \n\n");
	printf("-----------------------------------------------------\n\n");
*/
	list = read_xml(input_file_name, g_list_first(list));
//	printf("-----------------------------------------------------\n\n");
//	print_list(list);
	num_tasks = g_list_length(list);

/*


	printf("\n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	printf("            Passando de Lista Para Vetor             \n\n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
*/
	long period[num_tasks];
	long wcet[num_tasks];
	long offset[num_tasks];

	tasklist_to_vet(g_list_first(list), period, wcet, offset);
/*	printf("Period Vector:\t");
	print_vector(period, sizeof(period)/sizeof(long));
	printf("\n");
	printf("Wcet   Vector:\t");
	print_vector(wcet, sizeof(wcet)/sizeof(long));
	printf("\n");
	printf("Offset Vector:\t");
	print_vector(offset, sizeof(offset)/sizeof(long));
	printf("\n");

*/


// * CRIACAO DE TAREFAS COM VALORES MULTIPLICADOS
/*

	int x;
	long periodx2[num_tasks];
	long periodx3[num_tasks];
	long periodx4[num_tasks];

	for(x= 0; x < num_tasks; x++){

		periodx2[x] = period[x] * 2;
		periodx3[x] = period[x] * 3;
		periodx4[x] = period[x] * 4;

	}

	long last_wcet = wcet[num_tasks - 1];

	char *periodx2_text = "periodx2";

	char *periodx2_file_name= (char *) malloc(1 + strlen(input_file_name)+ strlen(periodx2_text) );
	strcpy(periodx2_file_name, periodx2_text);
	strcat(periodx2_file_name, input_file_name);

	char *periodx3_text = "periodx3";

	char *periodx3_file_name= (char *) malloc(1 + strlen(input_file_name)+ strlen(periodx3_text) );
	strcpy(periodx3_file_name, periodx3_text);
	strcat(periodx3_file_name, input_file_name);

	char *periodx4_text = "periodx4";

	char *periodx4_file_name= (char *) malloc(1 + strlen(input_file_name)+ strlen(periodx4_text) );
	strcpy(periodx4_file_name, periodx4_text);
	strcat(periodx4_file_name, input_file_name);

	wcet[num_tasks - 1] = last_wcet * 2;
	create_xml(periodx2_file_name, num_tasks, periodx2, wcet);

	wcet[num_tasks - 1] = last_wcet * 3;
	create_xml(periodx3_file_name, num_tasks, periodx3, wcet);

	wcet[num_tasks - 1] = last_wcet * 4;
	create_xml(periodx4_file_name, num_tasks, periodx4, wcet);

*/
/*
	printf("\n");
	printf("=====================================================\n\n");
	printf("            Passando de Lista Para Vetor Task        \n\n");
	printf("=====================================================\n\n");
*/
	task tasks[num_tasks];
	tasklist_to_taskvet(list, tasks);
//	print_tasks_vector(tasks, sizeof(tasks)/sizeof(task));
/*
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("           Algoritmo Utilizado			             \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
*/
//	printf("GLPK version: %s\n", glp_version());
	int is_feasible;
	long offsets[num_tasks];

/*
	// --- get start time ---
	time_t raw_start_time;
	time ( &raw_start_time );
*/
	glp_simplex_count = 0;

	switch(algoritmo){

	case 1:
		exhaustive_schedule_algoritm(num_tasks, tasks, offsets, period);
		break;
	case 2:
		is_feasible = calculate_feasible_offsets_lp_bckt_2(tasks, num_tasks);
		break;
	case 3:
		is_feasible = hrst1_calculate_feasible_offsets_lp_bckt_2(tasks, num_tasks, k);
		break;
	case 4:
		is_feasible = calculate_feasible_offsets_lp_2(tasks,num_tasks);
		break;
	default:
		break;
	}

	if(algoritmo == 1){
		/*
		printf("\n\n\n\n");
		printf("Offsets escalonaveis:\t");
		print_vector(offsets, num_tasks);
		printf("\n\n\n\n");
		*/
		//write_xml(output_file_name, num_tasks, period, wcet, offsets);
		is_valid_exit(period, wcet, offsets, num_tasks);
	}
	else{
		//print result
		if(is_feasible){
			int i;
			for(i = 0; i <= num_tasks - 1; i++){
			//	printf("Offset[%d]=%ld\n", i, tasks[i].offset);
			}
		}else{
			//printf("Could not find a solution\n");
		}

/*
		FILE *out = fopen(filetimes , "a");
		fprintf(out, "%d \t %d", glp_simplex_count, is_feasible);
		fclose(out);
*/

	}

/*
// --- get finish time ---
	time_t raw_end_time;
	time ( &raw_end_time );

// calculate and print time elapsed
	double rawtime_subtraction;
	rawtime_subtraction = difftime( raw_end_time, raw_start_time);
	printf("Time spent in seconds = %f\n\n",rawtime_subtraction);
*/

/*
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("           Testando Matriz de GCD's		             \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	long gcds[num_tasks][num_tasks];

	allocate_gcds_matrix(&gcds, num_tasks);
	init_gcds_matrix(gcds, num_tasks, period);
	print_matrix(gcds, num_tasks);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	printf("\n\n\n\n");
*/

/*

// --- get start time ---
	time_t raw_start_time;
	time ( &raw_start_time );

	long offsets[num_tasks];
	exhaustive_schedule_algoritm(num_tasks, tasks, offsets, period);

// --- get finish time ---
	time_t raw_end_time;
	time ( &raw_end_time );

// calculate and print time elapsed
	double rawtime_subtraction;
	rawtime_subtraction = difftime( raw_end_time, raw_start_time);
	printf("Time spent in seconds = %f\n\n",rawtime_subtraction);

	printf("\n\n\n\n");
	printf("Offsets escalonaveis:\t");
	print_vector(offsets, num_tasks);
	printf("\n\n\n\n");
	write_xml(output_file_name, num_tasks, period, wcet, offsets);
	is_valid_exit(period, wcet, offsets, num_tasks);


//_____________________________________________________________________________________

//								SECOND ALGORITHM
//_____________________________________________________________________________________


	printf("GLPK version: %s\n", glp_version());
	int is_feasible;

// --- get start time ---
	time ( &raw_start_time );

	//is_feasible = calculate_feasible_offsets_lp_bckt_2(tasks, num_tasks);
	//is_feasible = hrst1_calculate_feasible_offsets_lp_bckt_2(tasks, num_tasks);
	//is_feasible = calculate_feasible_offsets_lp_2(tasks,num_tasks);

	// --- get finish time ---
	time ( &raw_end_time );

	// calculate and print time elapsed
	rawtime_subtraction = difftime( raw_end_time, raw_start_time);
	printf("Time spent in seconds = %f\n\n",rawtime_subtraction);


	//print result
	if(is_feasible){
		int i;
		for(i = 0; i <= num_tasks - 1; i++){
			printf("Offset[%d]=%ld\n", i, tasks[i].offset);
		}
	}else{
		printf("Could not find a solution\n");
	}
*/
	return 0;
}


