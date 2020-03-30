#include "scheduler_exhaustive_search.h"

//___________________________________________________________________________________________________________
//min_m_ij

int min_m_ij(task Ti){

	return(Ti.wcet);

}

//___________________________________________________________________________________________________________
//max_m_ij

int max_m_ij(int gcd_ij, task Tj){

	return(		gcd_ij - Tj.wcet	);

}

//___________________________________________________________________________________________________________
//min_n_ij

int min_n_ij(int gcd_ij, int offset, task Tj){

	 return ceil(- (offset + max_m_ij(gcd_ij, Tj)) / gcd_ij);

}

//___________________________________________________________________________________________________________
//max_n_ij

int max_n_ij(int gcd_jj, int gcd_ij, int offset, task Ti){

	return floor(   (gcd_jj - 1 - offset - Ti.wcet) / gcd_ij    );

}


//___________________________________________________________________________________________________________
//Calcula Offset

int get_offset(int gcd_ij, int offset, int n, int m){

	return (offset + n * gcd_ij + m);

}


//___________________________________________________________________________________________________________
//Valida conjunto de Offsets

void remove_equivalent_offset(GList **valid, int gcd_jj){

	GList *list_intersec = *valid;
	*valid = NULL;
	int num;

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

void generate_offset(GList **generated_offsets, task taski, task taskj, int chosen_offset, int gcd_ij, int gcd_jj){

	int n, m;

	for (n = min_n_ij(gcd_ij, chosen_offset, taskj);
		 n <=  max_n_ij(gcd_jj, gcd_ij, chosen_offset, taski);  n++){

		for(m = min_m_ij(taski);
			m <= max_m_ij(gcd_ij, taskj);  m++){

				*generated_offsets = g_list_append(*generated_offsets,
				GINT_TO_POINTER(get_offset(gcd_ij, chosen_offset, n, m)));
		}
	}	
}


