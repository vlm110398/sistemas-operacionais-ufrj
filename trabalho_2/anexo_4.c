#include <stdio.h>
#include <unistd.h>

int main()
{
 int ret;
 ret = fork();
 if (ret == 0) {
    execl("/bin/ll","ll",(char*)0);
    printf("Por que este comando foi executado ? \n");
 }
 else
    printf("Processo continua executando.\n");
 return 0;
}
