#include <stdio.h>
#include <unistd.h>

int main()
{
 int ret;
 ret = fork();
 if (ret == 0) {
    execl("/bin/ls","ls",(char*)0);
    printf("Quando este comando ser� executado ? \n");
 };
 printf("Por que a fun��o printf anterior n�o foi executada?\n");
 return 0;
}

