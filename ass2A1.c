#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

void tokenize(char* cmd[], char* str){
    int index = 0;
    char* p;
    //strtok will seperate the words from string when space is occured and the first word will be stored in p and will store NULL if no words to tokenize.
    p = strtok(str," ");
    //run till there are no words to tokenize
    while(p != NULL){
        cmd[index] = p; //will add tokens to command array
        index++;
        p = strtok(NULL," "); //It tells to continue splitting the same string
    } 

    cmd[index] = NULL;
        
}
//Op stands for operation fex cc , wc , lc
void count(char* fn,char op) {  
    int cc = 0 , wc = 0 , lc = 0 , fh; //cc - character count , wc - word count , lc - line count  , fh - file handler
    char c; // used to iterate and store characters of string or file
    fh = open(fn,O_RDONLY);

    if(fh == -1){
        printf("File %s Not found",fn);
        return;
    }

    //will read one element at a time from filename(fn) and store it in var c will return 0 if there is no element left to traverse in file
    while(read(fh,&c,1)>0){
        if(c == ' '){
            wc++; //if space occurs word count increase
        }
        else if(c == '\n'){
            wc++; //if new line occurs word count and line count increase
            lc++;
        }
        cc++; //normally increase char count
    }
    close(fh);

    switch(op){
        case 'c' : printf("No. of characters %d\n",cc);
                    break;
        case 'w' : printf("No. of words %d\n",wc);
                    break;
        case 'l' : printf("No. of lines %d\n",lc);
                    break;
    }
}

int main(){
    char buff[80] , *cmd[10]; //buff to get command and cmd is seperated commands tokenized
    int pid;

    while(1){
        printf("myshell$");
        fflush(stdin); //clearing standard inpout
        fgets(buff,80,stdin); //it reads from stdin(standard input keyboard) copy it to buff array it can copy max 80 chars (used to take command)
        buff[strlen(buff) - 1] = '\0'; //adding termination to buff string at last
        tokenize(cmd,buff); //tokenize cmd in buff and stores it in cmd array which is 2d cmd[0] - count , cmd[1] - c or w or l , cmd[2] - file name
        if(strcmp(cmd[0],"count") == 0){
            count(cmd[2] , cmd[1][0]);
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