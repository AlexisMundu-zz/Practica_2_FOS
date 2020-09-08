#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int validate(char *user,char *pass){
	char fileUser[50],filePwd[50];
	FILE *fp;
    char buff[255];

	fp = fopen("passwd.txt","r");

    while(fgets(buff, 255, fp)){
        char *user_db = strtok(buff, ":");
        char *pass_db = strtok(NULL, "\n");
        printf("user: %s\t user_db: %s\n", user, user_db);
        printf("pass: %s\t pass_db: %s\n", pass, pass_db);

        if(strcmp(user, user_db) == 0 && strcmp(pass, pass_db) == 0) {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
	return 0;
}

int main(){
	char user[50];
	char pwd[50];
	int pid;
	printf("Usuario:");
	scanf("%[^\n]%*c",user);
	printf("Contrasena:");
	scanf("%[^\n]%*c",pwd);	
	while(1){
		if(validate(user,pwd) != 0){
            printf("We are in the shell");
            execlp("sh", "sh", NULL, NULL, NULL);
		}else{
			printf("Usuario:");
			scanf("%[^\n]%*c",user);
			printf("Contrasena:");
			scanf("%[^\n]%*c",pwd);	
		}
	}
	exit(0);
}

