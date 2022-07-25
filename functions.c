#include "headers.h"
void check_ta(int lab_no)
{
    bool ind = false;
    for (int i = 0; i < Labs[lab_no].num_ta; i++)
    {
        if (Labs[lab_no].tas[i].num_taship < Labs[lab_no].max_times_ta)
        {
            ind = true;
        }
    }
    if (ind == false && Labs[lab_no].availability != -1)
    {
        Labs[lab_no].availability = -1;
        printf(ANSI_COLOR_MAGENTA "Lab %s no longer has students available for TA ship\n" ANSI_COLOR_RESET , Labs[lab_no].name);
    }
}
int check_lab(course *c)
{
    cnt = 0;
    ind = 0;
    for (int i = 0; i < c->num_labs; i++)
    {
        for (int j = 0; j < Labs[c->lab_list[i]].num_ta; j++)
        {
            if (Labs[c->lab_list[i]].tas[j].num_taship < Labs[c->lab_list[i]].max_times_ta)
            {
                return 0;
            }
        }
    }

    c->course_removed = 1;
    printf(ANSI_COLOR_YELLOW "Course %s doesn't have any TA's eligible and is removed from course offerings" ANSI_COLOR_RESET "\n", c->name);

    for (int i = 0; i < total_students; i++)
    {
        if (Students[i].pref[Students[i].current_pref] == c - Courses)
        {
            pthread_mutex_lock(&Students[i].student_mutex);
            Students[i].course = c - Courses;
            pthread_cond_signal(&Students[i].student_cond);
            pthread_mutex_unlock(&Students[i].student_mutex);
        }
    }
    return 1;
}