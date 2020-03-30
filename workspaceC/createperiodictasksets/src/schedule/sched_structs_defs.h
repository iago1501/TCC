#ifndef SCHED_STRUCTS_DEFS_H

#define SCHED_STRUCTS_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mxml.h>
#include <glib.h>
#include <time.h>

#define MAX_NUM_TASKS 25

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
