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
            if (pid == 0) 
                execl("/bin/sh", "/bin/sh", "-c", command, NULL);
            wait(NULL);//wait for that child process to end
        }

    }while (strcmp(command, "exit") != 0 && strcmp(command, "shutdown") != 0); 
    
    if (strcmp(command, "exit") == 0)
        exit(0); 
    else    // command is shutdown
        execlp("killall", "killall", "xterm", "init", NULL); //kill absolutely all processes (init, getty and sh processes)

}