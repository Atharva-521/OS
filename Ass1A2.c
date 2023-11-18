#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    int pid;
    pid = fork();
    printf("Process id : %d\n",pid);
    if(pid == 0){
        printf("Child process id : %d\n priority : %d\n",getpid(),nice(-7));
    }
    else if(pid > 0){
        printf("parent process id : %d\n priority : %d\n",getppid(),nice(15));
    }
    else{
        printf("failed to create process");
    }
}