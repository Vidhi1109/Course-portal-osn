# Question 1

## To Run
``` gcc main.c courses.c functions.c students.c -lpthread```

Threads for following entities have been used:
<br>1.Courses
<br>2.Students

## Student Thread
Once a thread enters the function , sleep haults its execution until registration time .
<br>It then waits with conditional wait. It recieves a signal in 2 cases 
<br>1. Course is removed
<br>2. Student is selected and attended some tutorial.
<br>For case 1, the thread will again conditional wait if any of the preferences are left otherwise it will print an appropriate message and leave.
<br>For case 2, selection of course is decided on basis of probability. If course is not selected, the thread begins to do conditional wait for another course if any preference left otherwise leave the program.


## Course thread
Performs 3 tasks
<br>1. Check if lab has been removed
<br>2. Select a student for the course
<br>3. Check if tas are available in the lab and update information.
<br>It checks lab removal . If lab is available, it starts selecting students then tas.
<br>If no lab is available course is removed. 
