// Written by Group 3 OS Section 5, Taufiq Syahmi Auni Zulaikha

#include <stdio.h>
#include <unistd.h>

int main()
{
    int id_parent = getpid();
    // Parent @ original process
    printf("I am the PARENT, my process identifier is %d, my clones are:\n", id_parent);

    int pid_child1 = fork(); // Original create first child process (clone 1)

    if (pid_child1 == 0)
    { // Clone 1 will print
        printf("I am the obsolete VERSION; the recent version is %d\n", getpid());

        int pid_child2 = fork();
        // Clone 1 create it's own child
        if (pid_child2 == 0)
        {
            // Clone 2 will print
            printf("I am the new clone, process identifier of my parent is %d\n", getpid());
        }
    }
    else
    {
        // Original will have value pid_child1 > 1 thus
        // original will create second child process (clone 3)
        int pid_child3 = fork();
        if (pid_child3 == 0)
        { // Clone 3 will print
            printf("I am the SOPHISTICATED CLONE, process identifier of my parent is %d\n", getpid());

            // Clone 3 will make child, clone 4
            int pid_child4 = fork();
            if (pid_child4 == 0)
            {
                // Clone 4 will print
                printf("I am the most SOPHISTICATED CLONE, process identifier of my parent is %d\n", getpid());
            }
        }

        else
        {
            printf("process clone1: %d\nprocess clone3: %d\n", pid_child1, pid_child3);
        }
    }

    return 0;
}
