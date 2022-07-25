#include <assert.h>
#include <errno.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include "students.h"
#include "courses.h"
#include "labs.h"
#include "functions.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define tut_time 3

int total_students, total_courses, total_labs;
int students_selected[100];
int cnt;
int ind;

void *Students_init(void *);
void *Course_init(void *);
void *Lab_init(void *);

