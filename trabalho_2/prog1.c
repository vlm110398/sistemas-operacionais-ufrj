#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 64
#define READ 0
#define WRITE 1

// enum para definir tipo de mensagem trocada entre os pipes
typedef enum {
    string_t = 0,
    integer_t = 1
} MsgType;

// constroe mensagem com dado tipo
void* buildMessage(MsgType type, void* data, int size)
{
    void* msg = malloc(sizeof(MsgType) + size);
    memcpy(msg, &type, sizeof(MsgType));
    memcpy(msg + sizeof(MsgType), data, size);
    return msg;
}

// retorna tipo de mensagem
MsgType getMsgType(void* buffer)
{
    int t;
    memcpy(&t, buffer, sizeof(MsgType));
    return t;
}

int main(void)
{
    int status, cpid, ppid, j, pipeToChild[2], pipeToParent[2];
    
    if(pipe(pipeToParent) == -1 || pipe(pipeToChild) == -1) exit(EXIT_FAILURE); // criando pipes
    
    void* buffer = calloc(BUFFER_SIZE, sizeof(char)); // criando buffer
    if(buffer == NULL) exit(EXIT_FAILURE);
    
    //********* Insira um comando para pegar o PID do processo corrente e mostre na tela da console.
    ppid = getpid();
    printf("pid do processo atual: %d\n", ppid);
    
    //*** insira um comando para criar um subprocesso
    // executado pelo processo pai
    if(cpid = fork())
    {
        if(cpid == -1) exit(EXIT_FAILURE);
        //***** Faça com que o processo pai execute este trecho de código
        
        //***** Mostre na console o PID do processo pai e do processo filho
        printf("PAI -> pid processo pai: %d , pid processo filho: %d\n", getpid(), cpid);
        
        //***** Monte uma mensagem e a envie para o processo filho
        close(pipeToChild[READ]); // fechando canal de leitura
        char* messageToSend = "oi filho"; // mensagem
        if(write(pipeToChild[WRITE], messageToSend, strlen(messageToSend)) == -1)  // enviando mensagem
            printf("PAI -> falha ao enviar mensagem\n");
            
        //***** Mostre na tela o texto da mensagem enviada
        else printf("PAI -> mensagem enviada pelo processo pai: %s\n", messageToSend);
        close(pipeToChild[WRITE]); // fechando canal de escrita
        
        //***** Aguarde a resposta do processo filho
        //***** Mostre na tela o texto recebido do processo filho
        //***** Aguarde mensagem do filho e mostre o texto recebido
        close(pipeToParent[WRITE]); // fechando canal de escrita
        while(read(pipeToParent[READ], buffer, BUFFER_SIZE) > 0){
            if(getMsgType(buffer) == integer_t){ // inteiro (j)
                int value;
                memcpy(&value, buffer + sizeof(MsgType), sizeof(int));
                printf("PAI -> valor recebido do processo filho: %d\n", value);
            }
            else if(getMsgType(buffer) == string_t) { // string
                printf("PAI -> mensagem recebida do processo filho: %s\n", (char*)(buffer+sizeof(MsgType)));
            }
        }
        close(pipeToParent[READ]);
        
        //***** Aguarde o término do processo filho
        if(waitpid(-1, &status, 0) == -1) exit(EXIT_FAILURE);
        
        //***** Informe na tela que o filho terminou e que o processo pai também vai encerrar
        printf("PAI -> processo filho finalizado. finalizando processo pai\n");
        
    }
    // processo filho
    else {
        //***** Faça com que o processo filho execute este trecho de código
        
        //***** Mostre na tela o PID do processo corrente e do processo pai
        printf("FILHO -> pid processo pai: %d , pid processo filho: %d\n", getppid(), getpid());
        
        //***** Aguarde a mensagem do processo pai e ao receber mostre o texto na tela
        close(pipeToChild[WRITE]);
        printf("FILHO -> mensagem recebida do processo pai: ");
        while(read(pipeToChild[READ], buffer, 1) > 0)
            printf("%s", (char*)buffer);
        printf("\n");
        close(pipeToChild[READ]);
        
        //***** Envie uma mensagem resposta ao pai
        close(pipeToParent[READ]);
        char* message = "oi pai";
        void* msg1 = buildMessage(string_t, message, strlen(message));
        if(write(pipeToParent[WRITE], msg1, strlen(message) + sizeof(MsgType)) == -1)
            printf("FILHO -> falha ao enviar mensagem\n");
        else printf("FILHO -> mensagem enviada para processo pai: %s\n", message);
        
        //***** Execute o comando “for” abaixo
        for (j = 0; j <= 10000; j++);
        
        //***** Envie mensagem ao processo pai com o valor final de “j”
        void* msg2 = buildMessage(integer_t, &j, sizeof(int));
        if(write(pipeToParent[WRITE], msg2, sizeof(MsgType) + sizeof(int)) == -1)
            printf("FILHO -> falha ao enviar mensagem\n");
        printf("FILHO -> valor de j enviado: %d\n", j);
        close(pipeToParent[WRITE]);
        
        //***** Execute o comando abaixo e responda às perguntas
        if(execl("/Bin/ls", "ls", NULL) == -1)
            printf("FILHO -> erro na chamada execl\n");
        
        //***** O que acontece após este comando?
        // nada, pois o execl retorna erro (Bin ao inves de bin)
        
        //***** O que pode acontecer se o comando “execl” falhar?
        // a imagem do processo filho nao vai ser alterada, logo o programa ira finalizar
    }
    
    exit(0);
}