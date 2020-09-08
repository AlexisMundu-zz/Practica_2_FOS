#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    char command[100];
    int pid;

    do
    {
        printf("sh> ");
        scanf("%[^\n]%*c", command);
        if(strcmp(command, "shutdown") != 0){
            pid = fork();
            if (pid == 0) execl("/bin/sh", "/bin/sh", "-c", command, NULL);
            wait(NULL);//wait for that child process to end
        }

    } while (strcmp(command, "exit") != 0 && strcmp(command, "shutdown") != 0); 
    if (strcmp(command, "exit") == 0)
    {
        exit(0); // Sends exit program termination (0=successful), this will be used by getty
    }
    else
    {            // command is shutdown
        exit(1); // Sends shutdown status, this will be used by getty
    }
}