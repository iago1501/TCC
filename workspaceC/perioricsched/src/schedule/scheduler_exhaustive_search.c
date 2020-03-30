#include "scheduler_exhaustive_search.h"

//___________________________________________________________________________________________________________
//min_m_ij

int min_m_ij(task Ti){

	return(Ti.wcet);

}

//___________________________________________________________________________________________________________
//max_m_ij

int max_m_ij(long gcd_ij, task Tj){

	return(		gcd_ij - Tj.wcet	);

}

//___________________________________________________________________________________________________________
//min_n_ij

int min_n_ij(long gcd_ij, long offset, task Tj){

	 return ceil(    - (offset + max_m_ij(gcd_ij, Tj)) / gcd_ij       );

}

//___________________________________________________________________________________________________________
//max_n_ij

int max_n_ij(long gcd_jj, long gcd_ij, long offset, task Ti){

	return floor(   (gcd_jj - 1 - offset - Ti.wcet) / gcd_ij    );

}


//___________________________________________________________________________________________________________
//Calcula Offset

int get_offset(long gcd_ij, long offset, long n, long m){

	return (offset + n * gcd_ij + m);

}


//___________________________________________________________________________________________________________
//Valida conjunto de Offsets

void remove_equivalent_offset(GList **valid, long gcd_jj){

	GList *list_intersec = *valid;
	*valid = NULL;
	long num;

	while(list_intersec != NULL){
		num = GPOINTER_TO_INT(list_intersec->data);
		if(		(num >= 0)  && 	(num <= gcd_jj -1)	){
			*valid = g_list_append(*valid, list_intersec->data);
		}
		list_intersec = g_list_remove(list_intersec, list_intersec->data);
	}
}

//___________________________________________________________________________________________________________
//Gera Offsets

void generate_offset(GList **generated_offsets, task taski, task taskj, long chosen_offset, long gcd_ij, long gcd_jj){

	long n, m;

	for (n = min_n_ij(gcd_ij, chosen_offset, taskj);
		 n <=  max_n_ij(gcd_jj, gcd_ij, chosen_offset, taski);  n++){

		for(m = min_m_ij(taski);
			m <= max_m_ij(gcd_ij, taskj);  m++){

				*generated_offsets = g_list_append(*generated_offsets,
				GINT_TO_POINTER(get_offset(gcd_ij, chosen_offset, n, m)));
		}
	}	
}

//___________________________________________________________________________________________________________
//Algoritmo Principal de Escalonamento


void exhaustive_schedule_algoritm(long num_tasks, task *tasks, long *chosen_offsets, long *period){

	GList *offsets_intersec[num_tasks];
	GList *generated_offsets[num_tasks][num_tasks];
	
	long **gcds;
	allocate_gcds_matrix(&gcds, num_tasks);
	init_gcds_matrix(gcds, num_tasks, period);

	int recalc_s[num_tasks];
	int i, j, k;

	chosen_offsets[0] = 0;
	offsets_intersec[0] = NULL;

	for (i=0; i<num_tasks; i++) {
		recalc_s[i]=1;
	}

	for(j = 1; j < num_tasks; j++){
		
		i = 0;
		if (recalc_s[j] == 1){
			offsets_intersec[j] = NULL;
			generated_offsets[i][j] = NULL;
			generate_offset(&generated_offsets[i][j], tasks[i], tasks[j], chosen_offsets[i], gcds[i][j], gcds[j][j]);
		}

		offsets_intersec[j] = generated_offsets[i][j];		
		remove_equivalent_offset(&offsets_intersec[j], gcds[j][j]);
		for (i = 1; i < recalc_s[j]; i++){
			get_list_intersec(&offsets_intersec[j], generated_offsets[i][j]);
		}
		for (i = recalc_s[j];i < j; i++){
			generated_offsets[i][j] = NULL;
			generate_offset(&generated_offsets[i][j], tasks[i], tasks[j], chosen_offsets[i], gcds[i][j], gcds[j][j]);

			get_list_intersec(&offsets_intersec[j], generated_offsets[i][j]);
			g_list_free(generated_offsets[i][j]);
			remove_equivalent_offset(&offsets_intersec[j], gcds[j][j]);
		}
		while(offsets_intersec[j] == NULL){
			if(j > 0){
//				printf("\nTask_%03d não tem mais offsets para testar\n", j);
				j--;				
			}
			else{
//				printf("Sem solucao possivel\n");
				exit(1);
			}
		}

		k = j+1;
		while ( (k < num_tasks) && (recalc_s[k] > j) ){
			recalc_s[k] = j;
			k++;
		}

		chosen_offsets[j] = GPOINTER_TO_INT(offsets_intersec[j]->data);
		offsets_intersec[j] = g_list_remove(offsets_intersec[j], offsets_intersec[j]->data);
/*
		printf("\n");
		printf("Task_%03d pegou o offset de valor %ld\n", j, chosen_offsets[j]);
		printf("Offsets a testar para Task_%03d -> ", j);
		print_list_int(offsets_intersec[j]);
		printf("\n");
		*/

	}

}
