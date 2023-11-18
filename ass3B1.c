//non preemptive sjf


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

struct process{
    char pnm[20];
    int bt,at,wt,tat,ft,st;
};
struct process p[20];

float avg1 = 0 , avg2 = 0;
int n;

void accept(){
    for(int i = 1 ; i <= n ; i++){
        printf("\nEnter the process name : ");
        scanf("%s",p[i].pnm);
        printf("\nEnter burst time : ");
        scanf("%d",&p[i].bt);
        printf("\nEnter the arrival time : ");
        scanf("%s",&p[i].at);
    }
}

void display(){
    printf("\nprocess\t\tbt\tat\twt\ttat\tft");
    for(int i = 1 ; i <= n ; i++){
        printf("\n%s",p[i].pnm);
        printf("\t%d",p[i].bt);
        printf("\t%d",p[i].at);
        printf("\t%d",p[i].wt);
        printf("\t%d",p[i].tat);
        printf("\t%d",p[i].ft);
    }
    printf("\nAvg waiting time : %f",avg1);
    printf("avg turn around time : %f",avg2);
}

struct process temp;
void swap(int i, int j){
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
    printf("hello");
}

void sort(){
    for(int i = 1 ; i <= n ; i++){
        for(int j = i+1 ; j <= n ; j++){
            if(p[i].at > p[j].at){
                swap(i,j);
            }
        }
    }
}

int getprocess(int ctime){
    int min = 99 , y ;
    for(int i = 1 ; i <= n ; i++){
        if(p[i].bt <= min && p[i].at < ctime && p[i].bt != 0){
            min = p[i].bt;
            y = i;
        }
    }
    return y;
}

void sjf(){ 
    //every function like this is used for finding st and ft
    int time = 0;
    int x;
    for(int i = 1 ; i <= n ; i++){
        x = getprocess(time); // will get process with min burst time occured till current time
        p[x].st = time;
        while(p[x].bt != 0){
            p[x].bt--;
            time++;
        }
        p[x].ft = time;
    }
}

void avg(){
    int twt = 0 , ttat = 0; 
    for(int i = 1 ; i <= n ; i++){
        p[i].wt = p[i].st - p[i].at;
        p[i].tat = p[i].ft - p[i].at;
        twt = twt + p[i].wt;
        ttat = ttat + p[i].tat;
    }
    avg1 =(float)twt/n;
    avg2 = (float)ttat/n;
}

int main(){
    printf("Enter the number of process : ");
    scanf("%d",&n);

    accept();
    display();
    sort();
    sjf();
    avg();
    display();
}



