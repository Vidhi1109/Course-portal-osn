#include "headers.h"

// one thread per student
void *Students_init(void *input)
{
    student *s = (student *)input;

    sleep(s->entry_time);

    printf(ANSI_COLOR_BLUE "Students %ld has filled in preferences for course registration" ANSI_COLOR_RESET "\n", s - Students);

    s->availability = 1;

    while (1)
    {
        pthread_mutex_lock(&s->student_mutex);
    begin:
        s->course = -1;
        s->attending_tut = 0;
        // wait for a signal from course to indicate that a tutorial has been completed
        int course_num = s->pref[s->current_pref];
        if (Courses[course_num].course_removed == -1)
        {
            pthread_cond_wait(&s->student_cond, &s->student_mutex);
        }

        s->attending_tut = 0;

        // check if signal was because course has been removed
        // course has been removed
        // move to the next course which is available
        if (Courses[s->course].course_removed == 1)
        {
            if (s->current_pref == 2)
            {
                s->availability = -1;
                printf(ANSI_COLOR_RED "Student %ld couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s - Students);
                pthread_mutex_unlock(&s->student_mutex);
                return NULL;
            }
            else if (s->current_pref == 1)
            {
                if (Courses[s->pref[s->current_pref + 1]].course_removed == -1)
                {
                    s->current_pref++;
                    printf(ANSI_COLOR_BLUE "Student %ld has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s - Students, Courses[s->pref[s->current_pref - 1]].name, s->current_pref - 1, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else
                {
                    s->availability = -1;
                    printf(ANSI_COLOR_RED "Student %ld couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s - Students);
                    pthread_mutex_unlock(&s->student_mutex);
                    return NULL;
                }
            }
            else if (s->current_pref == 0)
            {
                if (Courses[s->pref[s->current_pref + 1]].course_removed == -1)
                {
                    s->current_pref++;
                    printf(ANSI_COLOR_BLUE "Student %d has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s->id, Courses[s->pref[s->current_pref - 1]].name, s->current_pref - 1, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else if (Courses[s->pref[s->current_pref + 2]].course_removed == -1)
                {
                    s->current_pref = s->current_pref + 2;
                    printf(ANSI_COLOR_BLUE "Student %d has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s->id, Courses[s->pref[s->current_pref - 2]].name, s->current_pref - 2, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else
                {
                    s->availability = -1;
                    printf(ANSI_COLOR_RED "Student %d couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s->id);
                    pthread_mutex_unlock(&s->student_mutex);
                    return NULL;
                }
            }
        }

        // student has completed the tut of some course
        s->attending_tut = 0;
        float probability = (s->calbre) * (Courses[s->pref[s->current_pref]].interest_quo) * 1.0;
        float random_value = ((float)rand() * 1.0) / RAND_MAX;

        if (random_value <= probability) // select this course
        {
            printf(ANSI_COLOR_MAGENTA  "Student %ld has selected the %s permanently" ANSI_COLOR_RESET "\n", s-Students, Courses[s->pref[s->current_pref]].name);
            Students[s-Students].finalise = 1;
            s->availability = -1;
            pthread_mutex_unlock(&s->student_mutex);
            return NULL;
        }
        else // change priority if this is not the third course or else exit the simulation
        {

            printf(ANSI_COLOR_CYAN "Student %ld has withdrawn from the %s course" ANSI_COLOR_RESET "\n", s-Students, Courses[s->pref[s->current_pref]].name);

            if (s->current_pref == 2)
            {
                s->availability = -1;
                printf(ANSI_COLOR_RED "Student %ld couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s - Students);
                pthread_mutex_unlock(&s->student_mutex);
                return NULL;
            }
            else if (s->current_pref == 1)
            {
                if (Courses[s->pref[s->current_pref + 1]].course_removed == -1)
                {
                    s->current_pref++;
                    printf(ANSI_COLOR_BLUE "Student %ld has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s - Students, Courses[s->pref[s->current_pref - 1]].name, s->current_pref - 1, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else
                {
                    s->availability = -1;
                    printf(ANSI_COLOR_RED "Student %ld couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s - Students);
                    pthread_mutex_unlock(&s->student_mutex);
                    return NULL;
                }
            }
            else if (s->current_pref == 0)
            {
                if (Courses[s->pref[s->current_pref + 1]].course_removed == -1)
                {
                    s->current_pref++;
                    printf(ANSI_COLOR_BLUE "Student %d has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s->id, Courses[s->pref[s->current_pref - 1]].name, s->current_pref - 1, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else if (Courses[s->pref[s->current_pref + 2]].course_removed == -1)
                {
                    s->current_pref = s->current_pref + 2;
                    printf(ANSI_COLOR_BLUE "Student %d has changed current preference from %s (priority %d) to %s (priority %d)" ANSI_COLOR_RESET "\n", s->id, Courses[s->pref[s->current_pref - 2]].name, s->current_pref - 2, Courses[s->pref[s->current_pref]].name, s->current_pref);
                    goto begin;
                }
                else
                {
                    s->availability = -1;
                    printf(ANSI_COLOR_RED "Student %d couldn't get any of his preferred courses" ANSI_COLOR_RESET "\n", s->id);
                    pthread_mutex_unlock(&s->student_mutex);
                    return NULL;
                }
            }
        }
    }
}