#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    int pid;
    printf("\n parent process: ");
    pid = fork();
    printf("Process id %d\n",pid);
    if(pid == 0){
        printf("Child process %d\n",getpid());
    }
    else if(pid > 0){
        printf("Parent id %d\n",getppid());
    }
    else{
        printf("Failed to create child process");
    }
}