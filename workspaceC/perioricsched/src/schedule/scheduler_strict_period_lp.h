/*
 *  scheduler_strict_period_lp.h
 *
 *  Created on: 23.07.2012
 *  Author: guerra
 */

#ifndef SCHEDULER_STRICT_PERIOD_LP_H_
#define SCHEDULER_STRICT_PERIOD_LP_H_

#define MAX_VAR_NAME_SIZE 255

#include <glpk.h>
#include "sched_data_types.h"
#include "sched_memory_init.h"
#include "sched_io.h"

/**
 * test
 *
 * @param offsets
 * @param num_tasks
 * @param periods
 * @param wcets
 * @return
 */
int calculate_feasible_offsets_lp(long* offsets, int num_tasks, long* periods, long* wcets);

/**
 *
 * @param tasks
 * @param num_tasks
 * @return
 */
int calculate_feasible_offsets_lp_2(struct task* tasks, int num_tasks);


/**
 *
 * @param m_glp_prob
 */
void init_lp_formulation(glp_prob* m_glp_prob);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @return
 */
int create_offset_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds);

/**
 *
 * @param tasks
 * @param num_tasks
 * @return
 */
int create_m_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @param wcets
 * @return
 */
int create_n_range_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, long* wcets);

/**
 *
 * @param m_glp_prob
 * @param num_tasks
 * @param gcds
 * @param ia
 * @param ja
 * @param ar
 * @param first_col_index_offset
 * @param first_col_index_m
 * @param first_col_index_n
 * @return
 */
int create_feasibility_contraints_lp(glp_prob* m_glp_prob, int num_tasks, long **gcds, int* ia, int* ja, double* ar, int first_col_index_offset, int first_col_index_m, int first_col_index_n);


#endif /* SCHEDULER_STRICT_PERIOD_LP_H_ */
