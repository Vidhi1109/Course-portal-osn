#ifndef STUDENT_H
#define STUDENT_H
typedef struct student
{
    int id;
    float calbre;
    int entry_time;
    int pref[3];
    int finalise;      // if 0 , it has not finalized else yes , it has finalalized
    int availability;  // will tell if student has filled its choices or not?
    int current_pref;  // tell which priority is it at this moment
    int attending_tut; // will tell if a student is in a tut or not?
    int course;        // tells which course he is planning to take // -1 means no signal was not sent from any course
    pthread_mutex_t student_mutex;
    pthread_cond_t student_cond;
} student;

student Students[500];
pthread_t Threads_student[500];

#endif