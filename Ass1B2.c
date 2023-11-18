#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    int pid;
    pid = fork();

    if(pid == 0){
        printf("Child process (PID %d)\n parent process(PID %d)\n",getpid(),getppid());
        sleep(5);
    }
    else if(pid > 0){
        printf("Parent process (PID %d)",getppid());
    }
    else{
        printf("Failed to creat echild process");
    }
}