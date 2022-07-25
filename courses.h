#ifndef COURSES_H
#define COURSES_H
typedef struct course
{
    int course_id;
    char name[256];
    float interest_quo;
    int max_slots;
    int num_labs;
    int lab_list[50];
    int course_removed;
} course;

course Courses[50];
pthread_t Threads_course[50];
int ta_id[50];
int lab_id[50] ;
#endif