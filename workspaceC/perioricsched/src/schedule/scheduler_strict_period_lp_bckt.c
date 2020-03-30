/*
 * scheduler_strict_period_lp_bckt.c
 *
 *  Created on: 23.07.2012
 *      Author: guerra
 */

#include "scheduler_strict_period_lp_bckt.h"

int calculate_feasible_offsets_lp_bckt_2(struct task* tasks, int num_tasks){

	long periods[num_tasks];

	long wcets[num_tasks];

	long offsets[num_tasks];

	int i;
	for(i = 0; i < num_tasks; i++){
		periods[i] = tasks[i].period;
		wcets[i] = tasks[i].wcet;
	}

	int is_feasible = calculate_feasible_offsets_lp_bckt(offsets, num_tasks, periods, wcets);

	if (is_feasible){
		for(i = 0; i < num_tasks; i++){
			tasks[i].offset = offsets[i];
		}
	}

	return is_feasible;
}

int calculate_feasible_offsets_lp_bckt(long* offsets, int num_tasks, long* periods, long* wcets){
	glp_prob* m_glp_prob = glp_create_prob();
	//length is MAX_NUM_TASKS*(MAX_NUM_TASKS-1)*2 because there are MAX_NUM_TASKS*(MAX_NUM_TASKS-1)/2 constraints with 4 variables
	//althought, 4 variables only in the MIP formulation, in the LP formulation there are 3 variables
	int ia[1 + num_tasks *(num_tasks - 1) *2], ja[1 + num_tasks *(num_tasks - 1) *2];
	double ar[1 + num_tasks *(num_tasks - 1) *2];

	int **n;
	allocate_n_matrix(&n, num_tasks);

	init_lp_formulation(m_glp_prob);

	//stores gcds of all periods pairwise to avoid recalculations
	// gcds[i][j] = gcds[j][i] = gcd(periods[i],periods[j])  ---  i<>j
	// gcds[i][i] = gcd(period[i],cum_lcm(i-1))
	long **gcds;
	allocate_gcds_matrix(&gcds, num_tasks);
	init_gcds_matrix(gcds, num_tasks, periods);

	//includes row constraints for the offset_i_range variables (search ranges of each offset)
	int first_col_index_offset = create_offset_range_contraints_lp_bckt(m_glp_prob,num_tasks,gcds);

	//includes row constraints for the m_j_i_range
	int first_col_index_m = create_m_range_contraints_lp_bckt(m_glp_prob,num_tasks,gcds,wcets);

	//initializes the n array with values that can potentially lead to a feasible solution --- branch and bound
	init_n_arrays(num_tasks, gcds, wcets, &n);

	//creates the coefficient arrays for the feasibility constraints
	int first_row_index;
	int k = init_feasibility_contraints_lp_bckt(m_glp_prob,num_tasks, ia, ja, ar, first_col_index_offset, first_col_index_m, &first_row_index);
	glp_load_matrix(m_glp_prob,k,ia,ja,ar);

	//holds the status of the lp_solution
	int solution_status;
	//counts number of iterations of the loop below --- one iterations for each combination of n values
	long num_iterations = 0;
	do{
		num_iterations++;
		if (num_iterations % 100000 == 0) {
			printf("trial number %ld\n\n",num_iterations);
			print_n_values(n,num_tasks);
		}

		//includes row constraints offset_j_offset_i to test pairwise feasibility
		//this constraints change depending of the values of n chosen
		update_feasibility_contraints_lp_bckt(m_glp_prob, num_tasks, gcds, first_row_index, n);

		//deactivate msgs while solving the lp problem
		glp_smcp parm;
		glp_init_smcp(&parm);
		parm.msg_lev = GLP_MSG_OFF;

		glp_simplex(m_glp_prob,&parm);

		solution_status = glp_get_status(m_glp_prob);
	}while ((solution_status != GLP_FEAS)&&(solution_status != GLP_OPT)&&( next_combination_n_values(num_tasks, gcds, wcets, &n) ));

	if ((solution_status == GLP_FEAS)||(solution_status == GLP_OPT)){
		//copy solution to offsets array given as input
		int i;
		for(i=0;i<=num_tasks-1;i++){
			offsets[i]=glp_get_col_prim(m_glp_prob,first_col_index_offset+i);
		}

		glp_write_lp(m_glp_prob,NULL,"m_glp_prob.txt");

		glp_print_sol(m_glp_prob,"solution.txt");
	}else{

		//no feasible solution
		return 0;
	}

	return 1;
}

int next_combination_n_values(int num_tasks, long **gcds, long *wcets, int ***n){
	int i,j;
	long offset_lb[num_tasks][num_tasks], offset_ub[num_tasks][num_tasks];

	int n_lb[num_tasks][num_tasks], n_ub[num_tasks][num_tasks];

	//init offset arrays
	for (i = 0; i < num_tasks; i++){
		for (j = 0; j < num_tasks; j++) {
			offset_lb[i][j] = 0;
			offset_ub[i][j] = LONG_MAX;
		}
	}
	offset_lb[0][0]=0;
	offset_ub[0][0]=0;

	//forces algorithm to look for a new combination of n values
	(*n)[num_tasks-1][num_tasks-2]++;

	int si_min, si_max;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){

			//update n_lb and n_ub based on current choice of n values
			n_lb[j][i] =  - (offset_ub[i][i] + gcds[i][j] - wcets[j]) / gcds[i][j];
			n_ub[j][i] = (gcds[j][j] - 1 - offset_lb[i][i] - wcets[i])/gcds[i][j];

			si_min = - ((*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j]);
			if (offset_lb[i][i] > si_min){
				si_min = offset_lb[i][i];
			}
			si_max = gcds[j][j] - 1 - ((*n)[j][i]*gcds[i][j] + wcets[i]);
			if (offset_ub[i][i] <  si_max){
				si_max = offset_ub[i][i];
			}

			//there is no need to update n_ub and n_lb, because these variable depend only on choices of n values of other tasks (these values haven't been changed)
			//update offset values for the new choice of n_j_i
			offset_lb[j][i+1] = si_min + (*n)[j][i]*gcds[i][j] + wcets[i];
			if (offset_lb[j][i] > offset_lb[j][i+1]){
				offset_lb[j][i+1] = offset_lb[j][i];
			}
			offset_ub[j][i+1] = si_max + (*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j];
			if (offset_ub[j][i] < offset_ub[j][i+1]){
				offset_ub[j][i+1] = offset_ub[j][i];
			}


			//while the current combination of n values is infeasible
			while(offset_lb[j][i+1]>offset_ub[j][i+1]){

				//try another value for n_j_i
				(*n)[j][i]++;

				//current n_j_i has reached its maximum value
				if ( (*n)[j][i] > n_ub[j][i] ){

					//reset n_j_i to its lowest possible value
					(*n)[j][i] = n_lb[j][i];

					//backtrack to n_j_(i-1)
					i--;

					//exhausted all n values for task j
					if (i < 0){

						//change n values for task (j-1)
						j--;
						i = j - 1;

						if(j == 0){
							//there are no more feasible combinations of n values
							return 0;
						}
					}

					//increment value for next try
					(*n)[j][i]++;
				}

				si_min = - ((*n)[j][i] * gcds[i][j] + gcds[i][j] - wcets[j]);
				if (offset_lb[i][i] > si_min){
					si_min = offset_lb[i][i];
				}
				si_max = gcds[j][j] - 1 - ((*n)[j][i]*gcds[i][j] + wcets[i]);
				if (offset_ub[i][i] <  si_max){
					si_max = offset_ub[i][i];
				}

				//there is no need to update n_ub and n_lb, because these variable depend only on choices of n values of other tasks (these values haven't been changed)
				//update offset values for the new choice of n_j_i
				offset_lb[j][i+1] = si_min + (*n)[j][i]*gcds[i][j] + wcets[i];
				if (offset_lb[j][i] > offset_lb[j][i+1]){
					offset_lb[j][i+1] = offset_lb[j][i];
				}
				offset_ub[j][i+1] = si_max + (*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j];
				if (offset_ub[j][i] < offset_ub[j][i+1]){
					offset_ub[j][i+1] = offset_ub[j][i];
				}
			}
		}
	}

	//successfully found a new combination of n values
	return 1;
}

void init_n_arrays(int num_tasks, long **gcds, long* wcets, int ***n){

	int i,j;
	long offset_lb[num_tasks][num_tasks], offset_ub[num_tasks][num_tasks];

	int n_lb[num_tasks][num_tasks], n_ub[num_tasks][num_tasks];

	//init offset arrays
	for (i = 0; i < num_tasks; i++){
		for (j = 0; j< num_tasks; j++) {
			offset_lb[i][j] = 0;
			offset_ub[i][j] = LONG_MAX;
		}
	}
	//first task scheduled ALWAYS has offset = 0
	offset_lb[0][0]=0;
	offset_ub[0][0]=0;

	long si_min, si_max;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){

			//update n_lb and n_ub based on current choice of n values
			n_lb[j][i] =  - (offset_ub[i][i] + gcds[i][j] - wcets[j]) / gcds[i][j];
			n_ub[j][i] = (gcds[j][j] - 1 - offset_lb[i][i] - wcets[i])/gcds[i][j];

			//initializes n with values of n_lb
			(*n)[j][i] = n_lb[j][i];

			si_min = - ((*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j]);
			if (offset_lb[i][i] > si_min){
				si_min = offset_lb[i][i];
			}
			si_max = gcds[j][j] - 1 - ((*n)[j][i]*gcds[i][j] + wcets[i]);
			if (offset_ub[i][i] <  si_max){
				si_max = offset_ub[i][i];
			}

			//there is no need to update n_ub and n_lb, because these variable depend only on choices of n values of other tasks (these values haven't been changed)
			//update offset values for the new choice of n_j_i
			offset_lb[j][i+1] = si_min + (*n)[j][i] * gcds[i][j] + wcets[i];
			if (offset_lb[j][i] > offset_lb[j][i+1]){
				offset_lb[j][i+1] = offset_lb[j][i];
			}
			offset_ub[j][i+1] = si_max + (*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j];
			if (offset_ub[j][i] < offset_ub[j][i+1]){
				offset_ub[j][i+1] = offset_ub[j][i];
			}

			//while the current combination of n values is infeasible
			while(offset_lb[j][i+1]>offset_ub[j][i+1]){

				//try another value for n_j_i
				(*n)[j][i]++;

				//current n_j_i has reached its maximum value
				if ( (*n)[j][i] > n_ub[j][i] ){

					//reset n_j_i to its lowest possible value
					(*n)[j][i] = n_lb[j][i];

					//backtrack to n_j_(i-1)
					i--;

					//exhausted all n values for task j
					if (i < 0){

						//change n values for task (j-1)
						j--;
						i = j - 1;

						if(j == 0){
							//there are no more feasible combinations of n values
							return;
						}
					}

					//increment value for next try
					(*n)[j][i]++;
				}

				si_min = - ((*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j]);
				if (offset_lb[i][i] > si_min){
					si_min = offset_lb[i][i];
				}
				si_max = gcds[j][j] - 1 - ((*n)[j][i]*gcds[i][j] + wcets[i]);
				if (offset_ub[i][i] <  si_max){
					si_max = offset_ub[i][i];
				}

				//there is no need to update n_ub and n_lb, because these variable depend only on choices of n values of other tasks (these values haven't been changed)
				//update offset values for the new choice of n_j_i
				offset_lb[j][i+1] = si_min + (*n)[j][i]*gcds[i][j] + wcets[i];
				if (offset_lb[j][i] > offset_lb[j][i+1]){
					offset_lb[j][i+1] = offset_lb[j][i];
				}
				offset_ub[j][i+1] = si_max + (*n)[j][i]*gcds[i][j] + gcds[i][j] - wcets[j];
				if (offset_ub[j][i] < offset_ub[j][i+1]){
					offset_ub[j][i+1] = offset_ub[j][i];
				}
			}
		}
	}
}

int create_offset_range_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds){
	return create_offset_range_contraints_lp(m_glp_prob, num_tasks, gcds);
}

int create_m_range_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets){
	return create_m_range_contraints_lp(m_glp_prob, num_tasks, gcds, wcets);
}

int init_feasibility_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, int* ia, int* ja, double* ar, int first_col_index_offset, int first_col_index_m, int* first_row_index){

	(*first_row_index) = glp_add_rows(m_glp_prob, num_tasks*(num_tasks-1)/2);
	int next_row_index = (*first_row_index);

	int k = 0;//index for the constraints' coefficients
	int i, j; //indexes for loops
	int loop_counter = 0;
	char string_buffer[MAX_VAR_NAME_SIZE];
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			sprintf(string_buffer,"offset_%d_offset_%d_feasibility",j,i);
			glp_set_row_name(m_glp_prob, next_row_index, string_buffer);

			//represents Si - Sj + m_j_i = - n_j_i*gcd(Ti,Tj) --- right term of equation done in function <update_feasibility_contraints_lp_bckt>
			k++;
			ia[k] = next_row_index;
			ja[k] = first_col_index_offset + i;
			ar[k] = 1.0;

			k++;
			ia[k] = next_row_index;
			ja[k] = first_col_index_offset + j;
			ar[k] = -1.0;

			k++;
			ia[k] = next_row_index;
			ja[k] =	first_col_index_m + loop_counter;
			ar[k] = 1.0;

			next_row_index++;
			loop_counter++;
		}
	}

	return k;
}

void update_feasibility_contraints_lp_bckt(glp_prob *m_glp_prob, int num_tasks, long **gcds, int first_row_index, int **n){

	int i, j; //indexes for loops
	int next_row_index = first_row_index;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			glp_set_row_bnds(m_glp_prob,next_row_index, GLP_FX, - n[j][i] * gcds[i][j], - n[j][i] * gcds[i][j]);
			next_row_index++;
		}
	}
}

void print_n_values(int **n, int num_tasks){
	int i,j,k=0;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			if (k % 4 == 0) {
				k=0;
				printf("\n");
			}
			k++;

			printf("n_%d_%d=%d \t",j,i,n[j][i]);
		}
	}
	printf("\n\n\n");

	return;
}
