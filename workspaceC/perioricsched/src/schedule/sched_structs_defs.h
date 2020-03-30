#ifndef SCHED_STRUCTS_DEFS_H

#define SCHED_STRUCTS_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mxml.h>
#include <glib.h>
#include <time.h>


#define MAX_NUM_TASKS 25

int glp_simplex_count;

struct task{

	long period, wcet, offset;

};

typedef struct task task;

struct GList {
  gpointer data;
  GList *next;
  GList *prev;
};

#endif
