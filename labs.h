#ifndef TA_H
#define TA_H
typedef struct ta
{
    int id;
    int course_id;    
    int num_taship;   
    int availability; 
} ta;
typedef struct lab
{
    int lab_id;
    char name[256];
    int max_times_ta;
    int num_ta;       // stores how many ta lab has  // ids are 0 indexed
    ta tas[51];       // stores the info about the tas in a lab
    int availability; // if 1 -> means ta some ta is there who has not completed its quota else 0
    int active_tas;   // stores how many tas are there who has not completed their quota
    //pthread_mutex_t tas_mutex[51];
} lab;
lab Labs[50];
pthread_t labThread[50];
pthread_mutex_t Tas_mutex[50][50];
ta *ta_info[50];
#endif