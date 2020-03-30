/*
 * scheduler_strict_period_lp_bckt_hrsts.h
 *
 *  Created on: 25.07.2012
 *      Author: guerra
 */

#ifndef SCHEDULER_STRICT_PERIOD_LP_BCKT_HRSTS_H_
#define SCHEDULER_STRICT_PERIOD_LP_BCKT_HRSTS_H_

#define MAX_NUM_N_VALUES_PER_TSKPAIR 50

#define DESC_SEARCH_TREE 1
#define ASC_SEARCH_TREE 0



#include <stdio.h>
#include "glpk.h"
#include <limits.h>
#include <string.h>
#include "scheduler_strict_period_lp_bckt.h"



//********variables, types and structures

/**
 *
 */
struct interval{
	int n_values[MAX_NUM_TASKS];
	long offset_lb;
	long offset_ub;
	long length;
	struct interval *prev, *next;
};

/**
 *
 */
struct glp_sched_prob{
	glp_prob* glp_prob;
	int first_col_index_offset;
	int first_col_index_m;
	int first_row_index;
};



//*** GLOBAL VARIABLES

struct interval* n_comb_set[MAX_NUM_TASKS];
int num_n_comb[MAX_NUM_TASKS];

struct interval n_selected_set[MAX_NUM_TASKS];
int num_n_selected_set;

struct glp_sched_prob m_glp_sched_probs_array[MAX_NUM_TASKS];



//******functions

/**
 *
 * @param tasks
 * @param num_tasks
 * @return
 */
int hrst1_calculate_feasible_offsets_lp_bckt_2(struct task *tasks, int num_tasks, int k);

/**
 *
 * @param offsets
 * @param num_tasks
 * @param periods
 * @param wcets
 * @return
 */
int hrst1_calculate_feasible_offsets_lp_bckt(long* offsets, int num_tasks, long* periods, long* wcets, int k);

/**
 *
 * @param num_tasks
 * @param gcds
 * @param periods
 * @param wcets
 * @return
 */
struct glp_sched_prob hrst1_create_lp_prob(int num_tasks, long **gcds, long* periods, long* wcets);

/**
 *
 * @param a
 * @param b
 * @return
 */
int cmp_interval_lengths(struct interval *a, struct interval *b);

/**
 *
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @param task_index
 */
void hrst1_create_search_intervals(int num_tasks, long **gcds, long* wcets, int task_index, int k);

/**
 *
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @return
 */
int hrst1_find_solution(int num_tasks, long **gcds, long* wcets, int k);

/**
 *
 * @param task_index
 */
void hrst1_select_search_interval(int task_index);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @param first_row_index
 */
void hrst1_update_feasibility_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds, int first_row_index);

/**
 *
 * @param num_tasks
 */
void print_n_selected_set_values(int num_tasks);

#endif /* SCHEDULER_STRICT_PERIOD_LP_BCKT_HRSTS_H_ */
