// premptive sjf - shortest job first here firstly we find process with shortest/ min burst time and do operation in it
//in fcfs we do operation(main function of program fex fcfs) on sorted array b ased on their arrival time
//in premptive sjf we do operation on thosew process who has minimum burst time
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

struct process{
    char pnm[20];
    int bt, wt, tat, st , ft , at , tbt ; //tbt total burst time
};
struct process p[20];

float avg1 = 0, avg2 = 0;

int n,totalbt = 0;

void accept(){
    for(int i = 1 ; i <= n ; i++){
        printf("\nEnter the process name : ");
        scanf("%s",p[i].pnm);
        printf("\nEnter the burst time : ");
        scanf("%d",&p[i].bt);
        totalbt = totalbt + p[i].bt;
        printf("\nEnter the arrival time : ");
        scanf("%d",&p[i].at);
    }
}

void display(){
    printf("\npname\t\tbt\tat\tft\ttat\twt");
    for(int i = 1 ; i<= n ; i++){
        printf("\n%s",p[i].pnm);
        printf("\t%d",p[i].bt);
        printf("\t%d",p[i].at);
        printf("\t%d",p[i].ft);
        printf("\t%d",p[i].tat);
        printf("\t%d",p[i].wt);
    }
    printf("\nAverage wait time : %f",avg1);
    printf("\nAverage turn around time : %f",avg2);
    printf("\nTotal burst time : %d",totalbt);
}
struct process temp;
swap(int i , int j){
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

void sort(){
    for(int i = 1 ; i <= n ; i++){
        for(int j = i + 1 ; j <= n ; j++){
            if(p[i].at > p[j].at){
                swap(i,j);
            }
        }
    }   
}
//function to get process having minimum burst time
int getprocess(int currt){ //currt - current time
    int min = 99, y = -1; //min - initial minimum time , y - index of process having minimum burst time
    for(int j = 1 ; j <= n ; j ++){
        if(p[j].bt <= min && p[j].at << currt && p[j].bt != 0){ 
            // if burst time is lesse than minimum time and arrival time is lesser than current time(means process has arrived earlier) and burstime is not zero
            min = p[j].bt; //updating min to new value
            y = j; //index of minimum burst time
        }
    }
    return y;
}

void sjfp(){
    int time = 0;
    int x;
    //perform the operation till the current time(time) is lesser than total execution time(total burst time)
    while(time <= totalbt){
        for(int i = 1; i <= n; i++){
            x = getprocess(time); //get the process having minimum burst time
            if(x == -1){ //if no process having burst time less than 99 is found
                time++;
            }
            else{
                //if process found then perform same operation ass ass3A1.c
                p[x].st = time; //current process start time = current time means at current time this process has started
                if(p[i].bt != 0){
                    p[i].bt--;
                    time++;
                }
                p[x].ft = time;
            }
        }
    } 
}

void avg(){
    int twt = 0 , ttat = 0;
    for(int i = 1 ; i <= n ; i++){
        //slight change in formula
        p[i].wt = p[i].st - (p[i].at + p[i].bt);
        p[i].tat = p[i].ft - p[i].at;
        twt = twt + p[i].wt;
        ttat = ttat + p[i].tat;
    }

    avg1 = (float)twt/n;
    avg2 = (float)ttat/n;
}

int main(){
    printf("\n Enter the number of process : ");
    scanf("%d",&n);
    accept();
    display();
    sort();
    sjfp();
    avg();
    display();
}