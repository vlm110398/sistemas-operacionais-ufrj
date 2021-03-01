#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(){
    char command[20];

    while(strcmp (command,"exit") != 0){
        scanf("%s", command);
        int ret = fork();
        if(ret == 0){
            char path[50] = "/bin/";
            strcat(path,command);
            fflush(stdout);
            execl(path, command, (char *) NULL);
            perror("");
        }
        else{
            int status;
            waitpid(ret, &status, 0); 
            if(WIFEXITED(status)){
                int exit_status = WEXITSTATUS(status);
                printf("Código de retorno = %d\n", exit_status);
            } 
            else{
                printf("Executado com sucesso\n");
            }
        }

    }
}