#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//returns 1 if user and password match, 0 if they do not
int validate(char *user,char *pass){
	FILE *fp;
    char buff[255];

	fp = fopen("passwd.txt","r");

    while(fgets(buff, 255, fp)){
        char *user_db = strtok(buff, ":");
        char *pass_db = strtok(NULL, "\n");
        if(strcmp(user, user_db) == 0 && strcmp(pass, pass_db) == 0) {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
	return 0;
}

void askForCredentials(char *user,char *pass){
	printf("Usuario:");
	scanf("%[^\n]%*c",user);
	printf("Contrasena:");
	scanf("%[^\n]%*c",pass);	
}

int main(){
	char user[50];
	char pwd[50];
	int pid;
	int status;
	askForCredentials(user,pwd);
	while(1){
		if(validate(user,pwd) == 1){
			//getty creates 1 child process that will be replaced by a shell session
			pid = fork();	
			if(pid == 0){ // if child 
				execlp("./sh","sh",NULL);
				exit(0);
			}else{
				wait(&status);//pickup exit status of sh
				if(status == 0){//user left shell with exit command, now ask for credentials again
					askForCredentials(user,pwd);
				}
				else{ //user left shell with shutdown command 
					//WE NEED TO LET INIT KNOW BUT HOW??
					//printf("SHUTDOWN TYPED GETTY");
					//sleep(4);
					exit(1); // Sends shutdown state to init
				}
			}
		}else{
			printf("Wrong credentials bro\n");
			askForCredentials(user,pwd);
		}
	}
	exit(0);
}

