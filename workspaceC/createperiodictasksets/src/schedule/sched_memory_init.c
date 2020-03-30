#include "sched_memory_init.h"

//___________________________________________________________________________________________________________
//Faz a alocação de uma struct task para poder inserir no ponteiro data da struct GList
task *set_task(int period, int wcet, int offset){


	task *tasks = (task*) malloc(sizeof(task));

	tasks->period = period;
	tasks->wcet = wcet;
	tasks->offset = offset;

	return tasks;

}

//___________________________________________________________________________________________________________
//Faz alocação de uma matrix do tipo int


int ** allocate_gcds_matrix(int num_tasks){

	int i, j;
	int ** gcd = (int **) malloc(num_tasks * sizeof(int*));
	  for (i = 0; i < num_tasks; i++){
	       gcd[i] = (int*) malloc(num_tasks * sizeof(int));
	       for (j = 0; j < num_tasks; j++){
	            gcd[i][j] = 0;
	       }
	  }
	return gcd;
}

void allocate_n_matrix(int ***n, int num_tasks){

	int i;
	*n = (int **) malloc(num_tasks * sizeof(int*));
	for(i = 0; i < num_tasks; i++)
		(*n)[i] = (int *) malloc (num_tasks * sizeof(int));

}

//_____________________________________________________________________________
//Maths to init


int gcd(int a, int b){

    int c = a % b;
    while(c != 0){

        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

int lcm(int a, int b){

    int c = gcd(a ,b);
    int d = a * b;
    return (d/c);

}

//___________________________________________________________________________________________________________
//Matriz espelho GCD

void init_gcds_matrix(int **gcds, int num_tasks, int *periods){

    int cum_lcm[num_tasks];

    gcds[0][0] = periods[0];
    cum_lcm[0] = periods[0];
    int i,j;
    for (j = 1; j <= num_tasks-1; j++){

        //initializes gcds[j][j] and cum_lcm[j]
        gcds[j][j] = gcd(periods[j],cum_lcm[j-1]);
        cum_lcm[j]= (periods[j] / gcds[j][j])*cum_lcm[j-1];

        for (i = 0; i < j; i++){
            gcds[i][j] = gcd(periods[i],periods[j]);
            gcds[j][i] = gcds[i][j];
        }
    }
}





