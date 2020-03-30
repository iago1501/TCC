/*
 * scheduler_strict_period_lp.c
 *
 *  Created on: 23.07.2012
 *      Author: guerra
 */

#include "scheduler_strict_period_lp.h"

int calculate_feasible_offsets_lp_2(struct task* tasks, int num_tasks){

	long periods[num_tasks];

	long wcets[num_tasks];

	long offsets[num_tasks];

	int i;
	for(i = 0; i < num_tasks; i++){
		periods[i] = tasks[i].period;
		wcets[i] = tasks[i].wcet;
	}

	int is_feasible = calculate_feasible_offsets_lp(offsets, num_tasks, periods, wcets);

	if (is_feasible){
		for(i = 0; i < num_tasks; i++){
			tasks[i].offset = offsets[i];
		}
	}

	return is_feasible;
}

void init_lp_formulation(glp_prob* m_glp_prob){
	glp_set_prob_name(m_glp_prob,"Find set of feasible offsets for each task");
	glp_set_obj_name(m_glp_prob,"There is no optimization goal");
	glp_set_obj_dir(m_glp_prob,GLP_MIN);
}

int create_offset_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds){

	int next_col_index = glp_add_cols(m_glp_prob, num_tasks);
	int first_col_index_offset = next_col_index;

	char string_buffer[MAX_VAR_NAME_SIZE];
	glp_set_col_name(m_glp_prob,next_col_index,"offset_0");
	glp_set_col_bnds(m_glp_prob,next_col_index,GLP_FX,0.0,0.0);
	glp_set_obj_coef(m_glp_prob, next_col_index, 0.0);
	next_col_index++;
	int i;
	for (i = 1; i <= num_tasks-1; i++){
		sprintf(string_buffer,"offset_%d",i);
		glp_set_col_name(m_glp_prob,next_col_index,string_buffer);
		glp_set_col_bnds(m_glp_prob,next_col_index,GLP_DB,0.0,gcds[i][i]-1);
		glp_set_obj_coef(m_glp_prob, next_col_index, 0.0);
		next_col_index++;
	}

	return first_col_index_offset;
}

int create_m_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets){

	int next_col_index = glp_add_cols(m_glp_prob, num_tasks*(num_tasks-1)/2);
	int first_col_index_m = next_col_index;
	char string_buffer[MAX_VAR_NAME_SIZE];
	int i,j;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			sprintf(string_buffer,"m_%d_%d_range",j,i);
			glp_set_col_name(m_glp_prob,next_col_index,string_buffer);
			glp_set_col_bnds(m_glp_prob,next_col_index,GLP_DB,wcets[i], gcds[i][j]-wcets[j]);
			glp_set_obj_coef(m_glp_prob, next_col_index, 0.0);
			next_col_index++;
		}
	}

	return first_col_index_m;
}

int create_n_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets){

	int next_col_index = glp_add_cols(m_glp_prob, num_tasks*(num_tasks-1)/2);
	int first_col_index_n = next_col_index;
	char string_buffer[MAX_VAR_NAME_SIZE];
	int i,j;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			sprintf(string_buffer,"n_%d_%d_range",j,i);
			glp_set_col_name(m_glp_prob,next_col_index,string_buffer);
			//ceiling and floors computed directly. Truncate a negative number = ceiling; Truncate a positive number = floor.
			glp_set_col_bnds(m_glp_prob,next_col_index,GLP_DB, - (gcds[i][i] - 1 + gcds[i][j] - wcets[j]) / gcds[i][j] , (gcds[j][j] - 1 - wcets[i])/gcds[i][j]);
			//tell to GLPK that this variable is integer
			glp_set_col_kind(m_glp_prob,next_col_index,GLP_IV);
			glp_set_obj_coef(m_glp_prob, next_col_index, 0.0);
			next_col_index++;
		}
	}

	return first_col_index_n;
}

int create_feasibility_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, int* ia, int* ja, double* ar, int first_col_index_offset, int first_col_index_m, int first_col_index_n){

	int next_row_index = glp_add_rows(m_glp_prob, num_tasks * (num_tasks - 1) / 2);
	int k = 0;//index for the constraints' coefficients
	int i, j; //indexes for loops
	int loop_counter = 0;
	char string_buffer[MAX_VAR_NAME_SIZE];
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			sprintf(string_buffer, "offset_%d_offset_%d_feasibility", j, i);
			glp_set_row_name(m_glp_prob, next_row_index, string_buffer);
			glp_set_row_bnds(m_glp_prob, next_row_index, GLP_FX,0.0,0.0);

			//represents Si - Sj + n_j_i*gcd(Ti,Tj) + m_j_i = 0 --- right term of equation done with function <glp_set_row_bnds> (see above)
			k++;
			ia[k] = next_row_index;
			ja[k] = first_col_index_offset + i;//Si
			ar[k] = 1.0;

			k++;
			ia[k] = next_row_index;
			ja[k] = first_col_index_offset + j;//Sj
			ar[k] = -1.0;


			// n_j_i * gcd(Ti,Tj)
			k++;
			ia[k] = next_row_index;
			ja[k] = first_col_index_n + loop_counter;//n_j_i
			ar[k] = gcds[i][j];//gcd(Ti,Tj))
			//#################################


			k++;
			ia[k] = next_row_index;
			ja[k] =	first_col_index_m + loop_counter;//m_j_i
			ar[k] = 1.0;

			next_row_index++;
			loop_counter++;
		}
	}

	return k;
}

int calculate_feasible_offsets_lp(long* offsets, int num_tasks, long* periods, long* wcets){

	glp_prob *m_glp_prob = glp_create_prob();
	//length is MAX_NUM_TASKS*(MAX_NUM_TASKS-1)*2 because there are MAX_NUM_TASKS*(MAX_NUM_TASKS-1)/2 constraints with 4 variables
	//althought, 4 variables only in the MIP formulation, in the LP formulation there are 3 variables
	int ia[1 + num_tasks * (num_tasks - 1) * 2], ja[1 + num_tasks * (num_tasks - 1) * 2];
	double ar[1 + num_tasks * (num_tasks - 1) * 2];

	init_lp_formulation(m_glp_prob);

	//stores gcds of all periods pairwise to avoid recalculations
	// gcds[i][j] = gcds[j][i] = gcd(periods[i],periods[j])  ---  i<>j
	// gcds[i][i] = gcd(period[i],cum_lcm(i-1))

	long **gcds;
	allocate_gcds_matrix(&gcds, num_tasks);
	init_gcds_matrix(gcds, num_tasks, periods);

	//includes row constraints for the offset_i_range variables (search ranges of each offset)
	int first_col_index_offset = create_offset_range_contraints_lp(m_glp_prob, num_tasks, gcds);

	//includes row constraints for the m_j_i_range
	int first_col_index_m = create_m_range_contraints_lp(m_glp_prob, num_tasks, gcds, wcets);

	//includes row constraints for the n_j_i_range
	int first_col_index_n = create_n_range_contraints_lp(m_glp_prob,num_tasks,gcds,wcets);

	//includes row constraints offset_j_offset_i to test pairwise feasibility
	int k = create_feasibility_contraints_lp(m_glp_prob, num_tasks, gcds, ia, ja, ar, first_col_index_offset, first_col_index_m, first_col_index_n);

	glp_load_matrix(m_glp_prob, k, ia, ja, ar);

	glp_write_lp(m_glp_prob, NULL, "m_glp_prob.txt");

	glp_adv_basis(m_glp_prob, 0);

	glp_simplex(m_glp_prob, NULL);

	glp_intopt(m_glp_prob, NULL);

	int i;
	for(i=0;i<=num_tasks-1;i++){
		offsets[i] = glp_mip_col_val(m_glp_prob, i + 1);
	}

	glp_print_mip(m_glp_prob,"solution.txt");

	return ((glp_mip_status(m_glp_prob) == GLP_OPT) || (glp_mip_status(m_glp_prob) == GLP_FEAS));
}


