#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILDREN 6

void main()
{
    int pid;
    int i;
    int parent = getpid();

    // init creates 6 child processes that will be replaced by getty processes
    for (i = 0; i < CHILDREN; i++)
    {
        if (getpid() == parent)
            pid = fork();
        if (pid == 0)
        {
            // Exec with xterm
            execlp("xterm", "xterm", "-e", "./getty", NULL);
        }
    }
    //constantly check that all 6 processes are running
    while(1)
    {
        wait(NULL);
        // If the xterm window was manually closed, then create another xterm window BOOM
        if (getpid() == parent)
            pid = fork();
        if (pid == 0)
            execlp("xterm", "xterm", "-e", "./getty", NULL);
    }
}