# Trabalho 2 - Sistemas Operacionais


## Comandos

- fork: cria um processo filho, duplicando o processo que fez a chamada ao m�todo. O PID do processo pai se torna o PPID do processo filho.

- exec: fam�lia de m�todos para executar um novo processo em cima do processo que realizou a chamada

- execl: execu��o de um novo processo requerindo uma lista de argumentos

- wait: suspende execu��o do processo que chamou o m�todo at� que um de seus processos filhos finalize

- exit: finaliza o processo que chamou o m�todo

- getpid: retorna o PID do processo que chamou o m�todo

- getppid: retorna o PPID do processo que chamou o m�todo

- getopt: trata os argumentos recebidos pela linha de comando (argc e argv)

## Programas anexos

- Exemplo 1: o programa faz duas chamadas ao m�todo fork(), criando assim dois processos filhos. Ambos os processos filhos executam a fun��o printf.

- Exemplo 2: ap�s criado o processo filho, este executa o comando ls para mostrar os arquivos do diret�rios atual. O processo ls � executado em cima do processo filho originalmente criado (c�pia do processo pai). J� o processo pai executa o printf e finaliza a execu��o. 

- Exemplo 3: criado o processo filho, quando detectado ret = 0 (significa que estamos no processo filho) iremos executar o processo ls. Como o processo ls ir� sobrescrever o processo filho original, nunca iremos executar a chamada ao printf("Quando este comando sera executado?\n").

- Exemplo 4: o printf foi executado pois a chamada execl falhou (retorno -1). O erro se deve ao fato de 'll' ser um alias para 'ls -l' e n�o um programa em si. Como o processo filho n�o � modificado, ele imprime a mensagem "Por que este comando foi executado?" no terminal.

## Programa 1

Respostas dentro do c�digo

### Sa�da do console

```
pid do processo atual: 2768
PAI -> pid processo pai: 2768 , pid processo filho: 2769
PAI -> mensagem enviada pelo processo pai: oi filho
FILHO -> pid processo pai: 2768 , pid processo filho: 2769
FILHO -> mensagem recebida do processo pai: oi filho
FILHO -> mensagem enviada para processo pai: oi pai
FILHO -> valor de j enviado: 10001
PAI -> valor recebido do processo filho: 10001
PAI -> mensagem recebida do processo filho: oi pai
PAI -> processo filho finalizado. finalizando processo pai
```

## Programa 2

### Premissas