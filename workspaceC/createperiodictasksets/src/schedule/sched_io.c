#include "sched_io.h"


//___________________________________________________________________________________________________________
//Criação de um XML teste



void create_xml(char *file, int num_tasks, int *set_periods, int *set_wcets) {

    mxml_node_t * xml;
    mxml_node_t * taskset;
    mxml_node_t * task;
    mxml_node_t * id;
    mxml_node_t * period;
    mxml_node_t * wcet;
    int i;


    FILE *fp;


    fp = fopen(file, "w");

    xml = mxmlNewXML("1.0");

        taskset = mxmlNewElement(xml, "Taskset");

        for( i = 0; i < num_tasks; i++){

        	task = mxmlNewElement(taskset,"Task");

                id = mxmlNewElement(task, "ID");
                mxmlNewInteger(id, i+1);
                period = mxmlNewElement(task, "Period");
                mxmlNewInteger(period, set_periods[i]);
                wcet = mxmlNewElement(task, "Wcet");
                mxmlNewInteger(wcet, set_wcets[i]);
        }

    mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);

    fclose(fp);

}

//___________________________________________________________________________________________________________
//Escreve XML saida



void write_xml(char *file, int num_tasks, int *periods, int *wcets, int *offsets) {

    mxml_node_t * xml;
    mxml_node_t * taskset;
    mxml_node_t * task;
    mxml_node_t * id;
    mxml_node_t * period;
    mxml_node_t * wcet;
    mxml_node_t * offset;
    int i;

    FILE *fp;

    fp = fopen(file, "w");

    xml = mxmlNewXML("1.0");

        taskset = mxmlNewElement(xml, "Taskset");

        for( i = 0; i < num_tasks; i++){

        	task = mxmlNewElement(taskset,"Task");

                id 	= mxmlNewElement(task, "ID");
                mxmlNewInteger(id, i+1);
                period 	= mxmlNewElement(task, "Period");
                mxmlNewInteger(period, periods[i]);
                wcet 	= mxmlNewElement(task, "Wcet");
                mxmlNewInteger(wcet, wcets[i]);
                offset 	= mxmlNewElement(task, "Offset");
                mxmlNewInteger(offset, offsets[i]);
        }

    mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);

    fclose(fp);

}

//___________________________________________________________________________________________________________
//Leitura do XML...recebe arquivo e joga para Lista


GList *read_xml(char *file, GList *list){

    FILE *fp = NULL;
    mxml_node_t *period, *wcet, *task = NULL;
    mxml_node_t *xml = NULL;


    fp = fopen(file, "r");

    xml = mxmlLoadFile(NULL, fp, MXML_INTEGER_CALLBACK);

    task = mxmlFindElement(xml, xml, "Task", NULL, NULL, MXML_DESCEND);

    while(task != NULL){

		period = mxmlFindElement(task, xml, "Period", NULL, NULL, MXML_DESCEND);
		wcet   = mxmlFindElement(task, xml, "Wcet"  , NULL, NULL, MXML_DESCEND);

    	task = mxmlGetNextSibling(task);
    	list = g_list_append(list,
    			set_task(mxmlGetInteger(period), mxmlGetInteger(wcet), 0));
    }



    fclose(fp);
    return list;


}

//___________________________________________________________________________________________________________
//Printa Lista

void print_list(GList *l){

	int i = 1;

	while (l != NULL){

		task *content = l->data;

		printf("Task :%d\t Period = %ld\t Wcet = %ld\t\n",
				  i, content->period, content->wcet);
		i++;
	    l = g_list_next(l);
	  }
}


void print_list_int(GList *l){

	while (l != NULL){

		printf("%d\t",GPOINTER_TO_INT(l->data));
	    l = g_list_next(l);
	  }

}


//___________________________________________________________________________________________________________
//Printa Vetor

void print_vector(int *vector, int size){

	int i;

	for(i = 0; i < size; i++){

		printf("%d\t", vector[i]);
	}
	printf("\n");
}

void print_tasks_vector(task *vector, int size){

	int i;
	for(i = 0; i < size; i ++){
		printf("TASK %d:\n Period = %ld \t Wcet = %ld \t Offset = %ld \n",i + 1, vector[i].period, vector[i].wcet, vector[i].offset);

	}


}

//___________________________________________________________________________________________________________
//Printa Matriz

void print_matrix(int **matrix, int size){

	int i,j;

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
}
