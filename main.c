#include "headers.h"
int main()
{
    scanf("%d %d %d", &total_students, &total_labs, &total_courses);
    for (int i = 0; i < total_courses; i++)
    {
        Courses[i].course_id = i;
        Courses[i].course_removed = -1;
        scanf("%s %f %d %d", Courses[i].name, &Courses[i].interest_quo, &Courses[i].max_slots, &Courses[i].num_labs);

        for (int j = 0; j < Courses[i].num_labs; j++)
        {
            scanf("%d", &Courses[i].lab_list[j]);
        }
    }
    for (int i = 0; i < total_students; i++)
    {
        scanf("%f %d %d %d %d", &Students[i].calbre, &Students[i].pref[0], &Students[i].pref[1], &Students[i].pref[2], &Students[i].entry_time);
        Students[i].id = i;
        Students[i].finalise = 0;
        Students[i].current_pref = 0;
        Students[i].availability = -1;
        Students[i].attending_tut = 0;
        Students[i].course = -1;
        pthread_mutex_init(&Students[i].student_mutex , NULL);
        pthread_cond_init(&Students[i].student_cond , NULL);
    }
    for (int i = 0; i < total_labs; i++)
    {
        scanf("%s %d %d", Labs[i].name, &Labs[i].num_ta, &Labs[i].max_times_ta);

        for (int j = 0; j < Labs[i].num_ta; j++)
        {
            Labs[i].tas[j].id = j;
            Labs[i].tas[j].course_id = -1;
            Labs[i].tas[j].num_taship = 0;
            Labs[i].tas[j].availability = 0;
            Labs[i].availability = 1;
            Labs[i].active_tas = Labs[i].num_ta;
        }

        Labs[i].lab_id = i;
    }
    for (int i = 0; i < total_labs; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            pthread_mutex_init(&Tas_mutex[i][j], NULL);
        }
    }
    for(int i=0 ; i<50 ; i++)
    {
        ta_id[i]=-1;
        lab_id[i]=-1;
    }
    for (int i = 0; i < total_students; i++)
        pthread_create(&Threads_student[i], NULL, Students_init, &Students[i]);

    for (int i = 0; i < total_courses; i++)
        pthread_create(&Threads_course[i], NULL, Course_init, &Courses[i]);

    for (int i = 0; i < total_students; i++)
        pthread_join(Threads_student[i], NULL);

    return 0;
}