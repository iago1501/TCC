/*
 * scheduler_strict_period_lp_bckt_hrsts.c
 *
 *  Created on: 25.07.2012
 *      Author: guerra
 */

#include <stdio.h>
#include <stdlib.h>
#include "glpk.h"
#include <limits.h>
#include <string.h>
#include <math.h>
#include "utlist.h"
#include "scheduler_strict_period_lp_bckt_hrsts.h"

int hrst1_calculate_feasible_offsets_lp_bckt_2(struct task *tasks, int num_tasks, int k){

	long periods[num_tasks];

	long wcets[num_tasks];

	long offsets[num_tasks];

	int i;
	for(i=0; i<num_tasks; i++){
		periods[i] = tasks[i].period;
		wcets[i] = tasks[i].wcet;
	}

	int is_feasible = hrst1_calculate_feasible_offsets_lp_bckt(offsets, num_tasks, periods, wcets, k);

	if (is_feasible){
		for(i=0; i<num_tasks; i++){
			tasks[i].offset = offsets[i];
		}
	}

	return is_feasible;
}

struct glp_sched_prob hrst1_create_lp_prob(int num_tasks, long **gcds, long* periods, long* wcets){

	glp_prob* m_glp_prob = glp_create_prob();

	//length is MAX_NUM_TASKS*(MAX_NUM_TASKS-1)*2 because there are MAX_NUM_TASKS*(MAX_NUM_TASKS-1)/2 constraints with 4 variables
	//althought, 4 variables only in the MIP formulation, in the LP formulation there are 3 variables
	int ia[1 + num_tasks * (num_tasks - 1) * 2], ja[1 + num_tasks * (num_tasks - 1) * 2];
	double ar[1 + num_tasks * (num_tasks - 1) * 2];

	init_lp_formulation(m_glp_prob);

	//includes row constraints for the offset_i_range variables (search ranges of each offset)
	int first_col_index_offset = create_offset_range_contraints_lp_bckt(m_glp_prob, num_tasks, gcds);

	//includes row constraints for the m_j_i_range
	int first_col_index_m = create_m_range_contraints_lp_bckt(m_glp_prob, num_tasks, gcds, wcets);

	//creates the coefficient arrays for the feasibility constraints
	int first_row_index;
	int k = init_feasibility_contraints_lp_bckt(m_glp_prob,num_tasks, ia, ja, ar, first_col_index_offset, first_col_index_m, &first_row_index);
	glp_load_matrix(m_glp_prob,k,ia,ja,ar);

	//store data in a struct
	struct glp_sched_prob m_glp_sched_prob;
	m_glp_sched_prob.glp_prob = m_glp_prob;
	m_glp_sched_prob.first_col_index_m = first_col_index_m;
	m_glp_sched_prob.first_col_index_offset = first_col_index_offset;
	m_glp_sched_prob.first_row_index = first_row_index;

	return m_glp_sched_prob;

}

int hrst1_calculate_feasible_offsets_lp_bckt(long *offsets, int num_tasks, long *periods, long *wcets, int k){

	//stores gcds of all periods pairwise to avoid recalculations
	// gcds[i][j] = gcds[j][i] = gcd(periods[i],periods[j])  ---  i<>j
	// gcds[i][i] = gcd(period[i],cum_lcm(i-1))

	long **gcds;
	allocate_gcds_matrix(&gcds, num_tasks);
	init_gcds_matrix(gcds, num_tasks, periods);

	//initialize n_comb_set[i] with NULL for usage with "utlist.h"
	int i;
	for(i=0;i<num_tasks;i++){
		n_comb_set[i]=NULL;
	}

	//create the intermediate LP problems that have to solved when traversing the search tree
	for(i=2;i<=num_tasks;i++){
		//only task sets with 2 or more tasks are considered
		//index within the <glp_probs_array> is the same as the index of the last task in the task set
		m_glp_sched_probs_array[i-1]=hrst1_create_lp_prob(i, gcds, periods, wcets);
	}

	//traverse the tree looking for a solution --- branch and bound
	int solution_status = hrst1_find_solution(num_tasks, gcds, wcets, k);

	if ((solution_status == GLP_FEAS)||(solution_status == GLP_OPT)){

		//print the selected n values for the solution found
		//print_n_selected_set_values(num_tasks);

		//copy solution to offsets array given as input
		int i;
		for(i=0;i<=num_tasks-1;i++){
			offsets[i]=glp_get_col_prim(m_glp_sched_probs_array[num_tasks-1].glp_prob,m_glp_sched_probs_array[num_tasks-1].first_col_index_offset+i);
		}

		//glp_write_lp(m_glp_sched_probs_array[num_tasks-1].glp_prob,NULL,"m_glp_prob.txt");

		//glp_print_sol(m_glp_sched_probs_array[num_tasks-1].glp_prob,"solution.txt");
	}else{

		//no feasible solution
		return 0;
	}

	//feasible solution found
	return 1;
}

int cmp_interval_lengths(struct interval *a, struct interval *b){
	return (a->length - b->length);
}

void hrst1_create_search_intervals(int num_tasks, long **gcds, long* wcets, int task_index, int k){

	long offset_lb[num_tasks], offset_ub[num_tasks];

	//used for improved readability of code
	long n_interval_start[num_tasks], n_interval_end[num_tasks];

	int n_lb[num_tasks];
	int n_ub[num_tasks];

	struct interval next_interval;

	int i;
	long SiMax, SiMin;
	for (i = 0; i < task_index; i++){

		//update n_lb and n_ub based on current choice of n values
		n_ub[i] = (gcds[task_index][task_index] - 1 - n_selected_set[i].offset_lb - wcets[i])/gcds[i][task_index];
		n_lb[i] =  - (n_selected_set[i].offset_ub + gcds[i][task_index] - wcets[task_index]) / gcds[i][task_index];

		//initialize n with the minimum values n_lb
		next_interval.n_values[i] = n_lb[i];

		//initialize offset values for all but the first task
		offset_lb[i] = 0;
		offset_ub[i] = LONG_MAX;

	}

	int n_comb_set_counter=0;
	i=0;
	do{
		while ( (i<task_index) && (next_interval.n_values[0]<=n_ub[0]) ){

			/**********update next_interval offsets (ub and lb)************/

			SiMin = - (next_interval.n_values[i]*gcds[i][task_index] + gcds[i][task_index] - wcets[task_index]);
			if (n_selected_set[i].offset_lb > SiMin){
				SiMin = n_selected_set[i].offset_lb;
			}
			SiMax = gcds[task_index][task_index] - 1 - (next_interval.n_values[i]*gcds[i][task_index] + wcets[i]);
			if (n_selected_set[i].offset_ub < SiMax ){
				SiMax = n_selected_set[i].offset_ub;
			}

			n_interval_start[i] = SiMin + next_interval.n_values[i]*gcds[i][task_index] + wcets[i];
			n_interval_end[i] = SiMax + next_interval.n_values[i]*gcds[i][task_index] + gcds[i][task_index] - wcets[task_index];

			offset_lb[i+1] = (offset_lb[i] < n_interval_start[i])?n_interval_start[i]:offset_lb[i];
			offset_ub[i+1] = (offset_ub[i] > n_interval_end[i] )?n_interval_end[i]:offset_ub[i];

			next_interval.offset_lb = offset_lb[i+1];
			next_interval.offset_ub = offset_ub[i+1];
			next_interval.length = next_interval.offset_ub - next_interval.offset_lb;

			//**********************


			//same as if statements below, but advancing n_value in a smarter way
			//experiments so far show no improvement in performance
			/*if (next_interval.length >= 0){
				//try next n value
				i++;
			}else if( // current n_value was reset to n_lb
					(i>0)
					&&
					(next_interval.n_values[i]==n_lb[i])
					&&
					(n_interval_start[i-1]-n_interval_end[i]>0)
				){

				//advance the current n value to a value closer to the current interval
				//TODO document this equation
				next_interval.n_values[i] += ceilf( ((float) n_interval_start[i-1]-n_interval_end[i])/gcds[i][task_index] );

			}else{
				if( //any value higher than the current will never result in a positive overlap with next_interval
						(i>0)
						&&
						(n_interval_start[i]>next_interval.offset_ub)
				){

					next_interval.n_values[i]=n_lb[i];
					i--;
				}

				//increment value for next try
				next_interval.n_values[i]++;
			}
			*/

			/******* EASY AND INTUITIVE SOLUTION TO ADVANCE N*************/
			//this combination of n values overlaps
			if (next_interval.length >= 0){
				//try next n value
				i++;
			}else{
				//increment current n value for next try
				next_interval.n_values[i]++;

				//if choice of n value exceeds the n_ub, reset value to n_lb and increment previous n value
				//increment in the previous value must also be checked against its n_ub
				//if i==0, leave the loop and the outter loop will also exit because n_value[0] will be 1 and n_ub[0] is always 0
				while((i>0)&&(next_interval.n_values[i]>n_ub[i])){
					next_interval.n_values[i]=n_lb[i];
					i--;

					//increment value for next try
					next_interval.n_values[i]++;
				}
			}

		}//while

		//a combination of n_values was found
		if (i==task_index){

			//allocate memory for this interval and append it to the list of intervals
			struct interval* new_element;
			if ( (new_element = (struct interval*) malloc(sizeof(struct interval)))==NULL){
				printf("System run out-of memory\n\n\n");
				exit(EXIT_FAILURE);
			}
			memcpy(new_element,&next_interval,sizeof(struct interval));
			DL_APPEND(n_comb_set[task_index],new_element);
			n_comb_set_counter++;


			//increment value of last n_value for next try
			i=task_index-1;
			next_interval.n_values[i]++;
		}

	//i=0 at this point when (next_interval.n_values[0] > n_ub[0]), condition to leave the inner while loop
	}while(i!=0);

	/* trims the search tree
	 *
	 * K<0 -> interval are visited in the order they are found
	 * K=0 -> interval are sorted in descending order of lengths. LArger interval generate LP problems that try more offset combinations
	 * K>0 -> for each task, only the n values yielding the k largest intervals are considered in the search
	 */
	if (k>0){
		//sorts the intervals in ascending order of lengths
		DL_SORT(n_comb_set[task_index],cmp_interval_lengths);
		while (n_comb_set_counter>k){
			struct interval *selected_element = n_comb_set[task_index];
			DL_DELETE(n_comb_set[task_index],n_comb_set[task_index]);
			free(selected_element);
			n_comb_set_counter--;
		}
	}else if (k==0){
		//sorts the interval in descending order of lengths
		DL_SORT(n_comb_set[task_index],- cmp_interval_lengths);
	}

//	printf("%d intervals for task t_%d\n\n",n_comb_set_counter,task_index);

	num_n_comb[task_index] = n_comb_set_counter;

	return;
}

int hrst1_find_solution(int num_tasks, long **gcds, long* wcets, int k){

	long backtracks_counter=0;

	//init values assuming task 0 is scheduled with offset=0
	num_n_comb[0]=0;
	n_selected_set[0].offset_lb = 0;
	n_selected_set[0].offset_ub = 0;
	n_selected_set[0].length = 0;
	num_n_selected_set = 1;

	//init values of num_n_comb for all tasks
	int i=0;
	for (i=0;i<num_tasks;i++){
		num_n_comb[i]=0;
	}

	//deactivate msgs while solving the lp problems
	glp_smcp parm;
	glp_init_smcp(&parm);
	parm.msg_lev = GLP_MSG_OFF;

	//traverse search tree to look for a feasible combination of n values
	int is_descending_flag = 1;
	int task_index = 1;
	int solution_status = GLP_INFEAS;//initialize as infeasible
	int simplex_status; //for debugging purposes
	while (task_index < num_tasks){

		while((task_index>0)&&(task_index > num_n_selected_set)){
			task_index--;
		}

		if(task_index==0){
			//no more combinations of n values possible

			return solution_status;
		}else if(num_n_comb[task_index]>0){//there are more intervals to try out for this task

			//select another interval
			hrst1_select_search_interval(task_index);

			//check whether current selection of n values yields a feasible schedule
			//num_tasks is equal to task_index+1, as task_index starts from 0
			hrst1_update_feasibility_contraints_lp_bckt(m_glp_sched_probs_array[task_index].glp_prob, task_index+1, gcds, m_glp_sched_probs_array[task_index].first_row_index);
			simplex_status = glp_simplex(m_glp_sched_probs_array[task_index].glp_prob,&parm);
			solution_status = glp_get_status(m_glp_sched_probs_array[task_index].glp_prob);
			glp_simplex_count ++;

			/*
			//DEBUG purpose
			switch (simplex_status){
			case 0:
				//printf("Found a solution \n\n");
				break;
			case GLP_EBADB:
				printf("GLP_EBADB \n\n");
				break;
			case GLP_ESING:
				printf("GLP_ESING \n\n");
				break;
			case GLP_ECOND:
				printf("GLP_ECOND \n\n");
				break;
			case GLP_EBOUND:
				printf("GLP_EBOUND \n\n");
				glp_write_lp(m_glp_sched_probs_array[task_index].glp_prob,NULL,"glp_bound_error.txt");
				break;
			case GLP_EFAIL:
				printf("GLP_EFAIL \n\n");
				break;
			case GLP_EOBJLL:
				printf("GLP_EOBJLL \n\n");
				break;
			case GLP_EOBJUL:
				printf("GLP_EOBJUL \n\n");
				break;
			case GLP_EITLIM:
				printf("GLP_EITLIM \n\n");
				break;
			case GLP_ETMLIM:
				printf("GLP_ETMLIM \n\n");
				break;
			case GLP_ENOPFS:
				printf("GLP_ENOPFS \n\n");
				break;
			case GLP_ENODFS:
				printf("GLP_ENODFS \n\n");
				break;
			}
			*/

			//if feasible
			if ((solution_status == GLP_OPT)||(solution_status == GLP_FEAS)){
				//go down the tree and try next task
				task_index++;
				is_descending_flag = 1;
			}else if ((solution_status == GLP_NOFEAS)||(solution_status == GLP_INFEAS)){
				//try next combination of n_values for task <task_index>
				//if there are no more combinations of n_values, code enter in this <else if>, otherwise code has to enter the last <else> statement and traverse the search tree upward
				is_descending_flag = 0;
			}else{//solver is not able to say whether there is a solution or not
				printf("LP Solver cannot tell whether the LP Problem has a solution or not --- status code: %d\n\n",solution_status);
				exit(1);
			}

		}else if (is_descending_flag){//searching down the tree -> intervals for current task have to be calculated

			hrst1_create_search_intervals(num_tasks, gcds, wcets, task_index, k);

			is_descending_flag = 0;

			//***choice of next interval to try will be done in the next iteraction of the outter loop**********//

		}else{//there is no interval to try out for this task and i am going up in the search tree

			backtracks_counter++;

			if (backtracks_counter%100000 == 0){
				print_n_selected_set_values(task_index+1);
			}

			//rollback
			num_n_selected_set--;
		}

	}

	printf("num backtracks = %ld\n\n",backtracks_counter);

	return solution_status;
}

void hrst1_select_search_interval(int task_index){
	//select last interval
	struct interval* selected_element = n_comb_set[task_index];
	DL_DELETE(n_comb_set[task_index],n_comb_set[task_index]);

	memcpy(&(n_selected_set[task_index]),selected_element,sizeof(struct interval));
	free(selected_element);

	//printf("n_selected_set[%d].length = %d --- %ld %ld\n\n", task_index, n_selected_set[task_index].length, n_selected_set[task_index].offset_ub, n_selected_set[task_index].offset_lb);

	//decrease number of available intervals to test
	num_n_comb[task_index]--;

	//increase number of currently selected sets of n values
	num_n_selected_set++;
}

void hrst1_update_feasibility_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds, int first_row_index){

	int i, j; //indexes for loops
	int next_row_index = first_row_index;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			glp_set_row_bnds(m_glp_prob,next_row_index,GLP_FX, - n_selected_set[j].n_values[i]*gcds[i][j], - n_selected_set[j].n_values[i]*gcds[i][j]);
			next_row_index++;
		}
	}

	return;
}

void print_n_selected_set_values(int num_tasks){
	int i,j,k=0;
	for (j = 1; j <= num_tasks-1; j++){
		for (i = 0; i < j; i++){
			if (k % 4 == 0) {
				k=0;
				printf("\n");
			}
			k++;

			printf("n_%d_%d=%d \t",j,i,n_selected_set[j].n_values[i]);
		}
	}
	printf("\n\n\n");

	return;
}
