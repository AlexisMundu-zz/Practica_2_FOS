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

    // init creates 6 child processes that will be replaced by getty processes
    for(i = 0; i < CHILDREN; i++){
        if(getpid() == parent)
            pid = fork();
        if(pid == 0){
            // Exec with xterm
            execlp("xterm", "xterm", "-e", "./getty", NULL);
        }
    }
    //constantly check that all 6 processes are running and also lookout for shutdown
    while(1) {
        wait(&status);
        sleep(3);
        //printf("%d", status);
        if(1){ // If shutdown command was typed in the shell, kill all xterm processes and terminate this init process
            execlp("killall", "killall", "xterm", NULL);
        //execl("/bin/sh", "/bin/sh", "-c", "kilall --user fsouser", NULL);
        exit(1);
        }
        
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