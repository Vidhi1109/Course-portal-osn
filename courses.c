#include "headers.h"

void *Course_init(void *input)
{
    course *c = (course *)input;
    int students_selected[100];
    int a = check_lab(c);
    if (a == 1)
    {
        return NULL;
    }
    while (1)
    {
        while (1)
        {
            cnt++;
            if (cnt > 15)
            {
                int x = check_lab(c);
                cnt = 0;
                if (x == 1)
                {
                    return 0;
                }
            }
            for (int i = 0; i < c->num_labs; i++)
            {
                for (int j = 0; j < Labs[c->lab_list[i]].num_ta; j++)
                {
                    if ((Labs[c->lab_list[i]].tas[j].availability == 0) && (Labs[c->lab_list[i]].tas[j].num_taship < Labs[c->lab_list[i]].max_times_ta))
                    {
                        if (pthread_mutex_trylock(&Tas_mutex[Labs[c->lab_list[i]].lab_id][j]) != 0)
                        {
                            continue;
                        }

                        Labs[c->lab_list[i]].tas[j].availability = 1;
                        Labs[c->lab_list[i]].tas[j].num_taship++;
                        Labs[c->lab_list[i]].tas[j].course_id = c->course_id;
                        ta_info[c-Courses] = &Labs[c->lab_list[i]].tas[j];
                        ta_id[c-Courses] = Labs[c->lab_list[i]].tas[j].id;
                        lab_id[c-Courses] = Labs[c->lab_list[i]].lab_id;
                        goto proceed;
                    }
                }
            }
        }
    proceed:

        printf(ANSI_COLOR_YELLOW "Course %s has been allocated TA %d from lab %s" ANSI_COLOR_RESET "\n", c->name, ta_id[c-Courses], Labs[lab_id[c-Courses]].name);

        printf(ANSI_COLOR_GREEN "TA %d from lab %s has been allocated to course %s for his %d taship" ANSI_COLOR_RESET "\n", ta_id[c-Courses], Labs[lab_id[c-Courses]].name, c->name, ta_info[c-Courses]->num_taship);

        int slots = (rand() % c->max_slots) + 1;

        printf("Course %s has been allocated %d seats\n", c->name, slots);

        int num_student_selected = 0;

        while (num_student_selected == 0)
        {
            for (int i = 0; i < total_students; i++)
            {

                if ((Students[i].availability != -1) && (Students[i].pref[Students[i].current_pref] == c->course_id) && (Students[i].attending_tut == 0))
                {
                    pthread_mutex_lock(&Students[i].student_mutex);
                    Students[i].attending_tut = 1;
                    students_selected[num_student_selected] = i;
                    Students[i].course = c->course_id;
                    num_student_selected++;

                    printf(ANSI_COLOR_GREEN "Student %d has been allocated a seat in course %s" ANSI_COLOR_RESET "\n", i, c->name);
                }

                if (num_student_selected >= slots)
                    break;
            }
        }

        printf("Tutorial has started for course %s with %d seats fulled out of %d\n", c->name, num_student_selected, slots);
        sleep(tut_time);



        printf("TA %d from lab %s has completed tut for course %s\n", ta_id[c-Courses], Labs[lab_id[c-Courses]].name, c->name);

        for (int i = 0; i < num_student_selected; i++)
        {
            pthread_mutex_unlock(&Students[students_selected[i]].student_mutex);
            pthread_cond_signal(&Students[students_selected[i]].student_cond);
        }

        ta_info[c-Courses]->availability = 0;

        check_ta(lab_id[c-Courses]);

        pthread_mutex_unlock(&Tas_mutex[lab_id[c-Courses]][ta_info[c-Courses]->id]);
    }
}
