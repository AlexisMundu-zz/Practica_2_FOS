#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILDREN 6

int main() {
    int pid;
    int i;
    int parent = getpid();
    int status;

    // Create all processes
    for(i = 0; i < CHILDREN; i++){
        if(getpid() == parent)
            pid = fork();
        if(pid == 0){
            // Exec with xterm
            execlp("xterm", "xterm", "-e", "./getty", NULL);
        }
    }

    while(1) {
        wait(&status);
        printf("Status: %d", status);
        // If status is 0 meaning window was closed, then create another xterm window BOOM
        if(status == 0) {
            if(getpid() == parent)
                pid = fork();
            if(pid == 0){
                execlp("xterm", "xterm", "-e", "./getty", NULL);
            }
        }
    }  
    return 0;
}