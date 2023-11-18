#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

void tokenize(char* cmd[],char* str){
    char* p;
    int index = 0;
    p = strtok(str," ");
    while(p != NULL){
        cmd[index] = p;
        index++;
        p = strtok(NULL," ");
    }
    cmd[index] = NULL;
}

void listop(char* dn,char op){
    DIR* dp; //creating directory pointer of data type DIR which is user defined structure with its own operations
    int dc = 0 , fc = 0; //directory count and file count
    struct dirent *entry; //creating an object for class dirent to handle or do operations on directories

    // dirent class has following operations :
    //     1. entry->d_type it return type of directory DT_REG for regular file and DT_DIR for directory .
    //     2. entry->d_name it returns name of directory.
    //     3. entry->d_fileno it return the number of current file in directory.
    //     4. readdir(dp) it return structure pointing to current file/dir , each time it runs it points to next file.

    dp = opendir(dn); //opens directory and dp points to that dir return NULL if no directory found
    if(dp == NULL){
        printf("No directory found of name %s\n",dn);
        return;
    }

    switch(op){
        case 'f' : 
            while(entry = readdir(dp)){
                // runs the loop till entry contains a file or directory from current directory when there are no dir to read entry will 
                // contain NULL and terminate loop
                //to display only filenames and not directory names
                if(entry->d_type == DT_REG){
                    // if only file
                    printf("%s\n",entry->d_name);
                }
            }
            break;
        case 'n' : 
            while(entry = readdir(dp)){
                if(entry->d_type == DT_REG){
                    // if file
                    fc++;
                }
                if(entry->d_type == DT_DIR){
                    // if directory
                    dc++;
                }
            }
            printf("File count : %d\n",fc);
            printf("Directory count : %d\n",dc);
            break;

        case 'i' :
            while(entry = readdir(dp)){
                if(entry->d_type == DT_REG){
                    // only file
                    printf("File name : %s\nInode : %d\n",entry->d_name,entry->d_ino);
                }
            }
            break;
    }


}

int main(){
    char buff[80], *cmd[10];
    int pid;
    while(1){
        printf("myshell$ ");
        fflush(stdin);
        fgets(buff,80,stdin);
        buff[strlen(buff) - 1] = '\0';
        tokenize(cmd,buff);
        
        if(strcmp(cmd[0],"list") == 0){
            listop(cmd[2],cmd[1][0]);
        }
        else{
            pid = fork();
            if(pid > 0){
                wait();
            }
            else{
                if(execvp(cmd[0],cmd) == -1){
                    printf("Bad command\n");
                }
            }
        }

    }
}