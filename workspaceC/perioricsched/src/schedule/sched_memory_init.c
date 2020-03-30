#include "sched_memory_init.h"

//___________________________________________________________________________________________________________
//Faz a alocação de uma struct task para poder inserir no ponteiro data da struct GList
task *set_task(long period, long wcet, long offset){


	task *tasks = (task*) malloc(sizeof(task));

	tasks->period = period;
	tasks->wcet = wcet;
	tasks->offset = offset;

	return tasks;

}

//___________________________________________________________________________________________________________
//Faz alocação de uma matrix do tipo int


void allocate_gcds_matrix(long ***gcds, int num_tasks){


	int i;
	*gcds = (long **) malloc(num_tasks * sizeof(long*));
	for(i = 0; i < num_tasks; i++)
		(*gcds)[i] = (long *) malloc (num_tasks * sizeof(long));
	
}

void allocate_n_matrix(int ***n, int num_tasks){

	int i;
	*n = (int **) malloc(num_tasks * sizeof(int*));
	for(i = 0; i < num_tasks; i++)
		(*n)[i] = (int *) malloc (num_tasks * sizeof(int));

}

//_____________________________________________________________________________
//Maths to init


long gcd(long a, long b){

    long c = a % b;
    while(c != 0){

        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

long lcm(long a, long b){

    long c = gcd(a ,b);
    long d = a * b;
    return (d/c);

}

//___________________________________________________________________________________________________________
//Matriz espelho GCD

void init_gcds_matrix(long **gcds, int num_tasks, long *periods){

    long cum_lcm[num_tasks];

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





