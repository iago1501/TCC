/*
 * scheduler_strict_period_lp_bckt.h
 *
 *  Created on: 23.07.2012
 *      Author: guerra
 */

#ifndef SCHEDULER_STRICT_PERIOD_LP_BCKT_H_
#define SCHEDULER_STRICT_PERIOD_LP_BCKT_H_

#include <glpk.h>
#include "scheduler_strict_period_lp.h"
#include <limits.h>
#include <string.h>
#include "sched_data_types.h"
#include "sched_memory_init.h"
#include "sched_io.h"

/**
 *
 * @param tasks
 * @param num_tasks
 * @return
 */
int calculate_feasible_offsets_lp_bckt_2(struct task* tasks, int num_tasks);

/**
 *
 * @param offsets
 * @param num_tasks
 * @param periods
 * @param wcets
 * @return
 */
int calculate_feasible_offsets_lp_bckt(long* offsets, int num_tasks, long* periods, long* wcets);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @return
 */
int create_offset_range_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @return
 */
int create_m_range_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param ia
 * @param ja
 * @param ar
 * @param first_col_index_offset
 * @param first_col_index_m
 * @param first_row_index
 * @return
 */
int init_feasibility_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, int* ia, int* ja, double* ar, int first_col_index_offset, int first_col_index_m, int* first_row_index);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @param first_row_index
 * @param n
 */
void update_feasibility_contraints_lp_bckt(glp_prob* m_glp_prob, int num_tasks, long **gcds, int first_row_index, int **n);

/**
 *
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @param n
 */
void init_n_arrays(int num_tasks, long **gcds, long* wcets, int ***n);

/**
 *
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @param n
 * @return
 */
int next_combination_n_values(int num_tasks, long **gcds, long* wcets, int ***n);

/**
 *
 * @param n
 * @param num_tasks
 */
void print_n_values(int **n, int num_tasks);

#endif /* SCHEDULER_STRICT_PERIOD_LP_BCKT_H_ */
