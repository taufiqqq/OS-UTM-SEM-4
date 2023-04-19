// Written by Group 3 OS Section 5, Taufiq Syahmi Auni Zulaikha

#include <stdio.h>
#include <unistd.h>

int main()
{
    int id_parent = getpid();
    //Parent process
    printf("I am the PARENT, my process identifier is %d, my clones are:\n", id_parent);

    int pid_child1 = fork();
    //Parent create first child process
    if (pid_child1 == 0)
    {
        printf("I am the obsolete VERSION; the recent version is %d\n", getpid());

        int pid_child2 = fork();
        if (pid_child2 == 0)
        {
            printf("I am the new clone, process identifier of my parent is %d\n", getpid());
        }
    }
    else
    {
        int pid_child3 = fork();
        if (pid_child3 == 0)
        {
            printf("I am the SOPHISTICATED CLONE, process identifier of my parent is %d\n", getpid());

            int pid_child4 = fork();
            if (pid_child4 == 0)
            {
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
