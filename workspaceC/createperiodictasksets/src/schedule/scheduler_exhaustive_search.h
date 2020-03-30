#ifndef SCHEDULER_EXHAUSTIVE_SEARCH_H

#define SCHEDULER_EXHAUSTIVE_SEARCH_H

#include "sched_data_types.h"
#include "sched_memory_init.h"
#include "sched_io.h"


//___________________________________________________________________________________________________________
//min_Mij

int min_m_ij(task Ti);

//___________________________________________________________________________________________________________
//max_Mij

int max_m_ij(int gcd_ij, task Tj);

//___________________________________________________________________________________________________________
//min_Nij

int min_n_ij(int gcd_ij, int offset, task Tj);

//___________________________________________________________________________________________________________
//max_Nij

int max_n_ij(int gcd_jj, int gcd_ij, int offset, task Ti);

//___________________________________________________________________________________________________________
//Calcula Offset

int get_offset(int gcd_ij, int offset, int n, int m);

//___________________________________________________________________________________________________________
//Valida conjunto de Offsets

void remove_equivalent_offset(GList **valid, int gcd_jj);

//___________________________________________________________________________________________________________
//Gera Offsets

void generate_offset(GList **generated_offsets, task taski, task taskj, int chosen_offset, int gcd_ij, int gcd_jj);


#endif

