// Written by Group 3 OS Section 5, Taufiq Syahmi Auni Zulaikha

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int id_parent = getpid();
    int pid_child1, pid_child2, pid_child3, pid_child4;

    // Parent @ original process
    printf("I am the PARENT, my process identifier is %d, my clones are:\n", id_parent);

    pid_child1 = fork(); // Original create first child process (clone 1)
    if (pid_child1 == 0)
    {
        // Clone 1 create it's own child
        pid_child2 = fork();
        if (pid_child2 > 0)
            printf("I am the obsolete VERSION; the recent version is %d\n", pid_child2); // Clone 1 will print
    }
    else
    {
        // Original will have value pid_child1 > 1 thus
        // original will create second child process (clone 3)
        pid_child3 = fork();
        if (pid_child3 == 0)
        {
            // Clone 3 will make child, clone 4
            pid_child4 = fork();
            if (pid_child4 == 0)
            {
                // Clone 4 will print, and utilize getppid() to get parent id
                printf("I am the most SOPHISTICATED CLONE, process identifier of my parent is %d\n", getppid());
            }
        }

        else
        {
            printf("process clone1: %d\nprocess clone3: %d\n", pid_child1, pid_child3);
        }
        wait(NULL);
    }

    return 0;
}
