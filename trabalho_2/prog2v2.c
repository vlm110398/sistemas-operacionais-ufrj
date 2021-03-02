#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

int main(){
    char line[500];
    char line_cpy[500];
    char f1[20];
    char f2[20];
    char *command;
    int stop = FALSE;
    int num_args;
    int i;
    while(stop == FALSE){
        fgets(line,500, stdin);
        line[strcspn(line, "\n")] = 0;
        strcpy(line_cpy,line);
        char *word = strtok(line_cpy, " ");
        command = word;
        for(num_args = 0; word != NULL; num_args++){          
            word = strtok(NULL, " ");
            //printf("%s\n", word);
            
        }
        strcpy(line_cpy,line);
        word = strtok(line_cpy, " ");
        char ** args = (char **) malloc(sizeof(char *)* num_args);
        args[0] = word;
        if(strcmp (word,"exit") == 0){
            break;
        }
        for(i = 1; i < num_args ; i++ ){
            word = strtok(NULL, " ");
            if(strcmp (word,"exit") == 0){
                stop = TRUE;
            }
            args[i] = word;  
            //printf("%s\n", word);         
        }
        if(stop == TRUE){
            break;
        }        
         
        int ret = fork();
        if(ret == 0){
            //char path[50] = "/bin/";
            //strcat(path,command);
            fflush(stdout);
            //printf("%s\n", command);
            for(i = 0; i < num_args; i++){
                //printf("%s\n", args[i]);
            }
            execvp(command,args);
            //perror("");
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
        memset(command, 0, sizeof(command)); 
        memset(line, 0, sizeof(line));
        memset(line_cpy, 0, sizeof(line_cpy));      
    }
}