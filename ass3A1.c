// fcfs
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

// create a class to store all info of process fex process name , bt,wt,tat,ft,st
struct process{
    char pnm[10]; //process name string
    int bt,at,wt,tat,ft,st; 
    //bt - burst time(execution time of process) , at- arrival time of process in memory , wt - waiting time of process
    //tat - turn arount time, ft - fininsh time of process , st - start time of process
    //formulaes
    // wt = st - at
    // tat = ft - at
    // twt = twt1 + wt , total wait time
    // ttat = ttot + tat , total turn around time

};
struct process p[20]; //created array of 10 processes
int n ; // No. of process

struct process temp; // temprory process for swapping purposes

float avg1 = 0 , avg2 = 0;

//swap function for sorting
void swap(int i , int j){
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

//function to accept a new process with its detail
void accept(){
    for(int i = 1 ; i <= n ; i ++){
        printf("\nEnter the process name : ");
        scanf("%s",p[i].pnm);
        printf("\nEnter the burst time : ");
        scanf("%d",&p[i].bt);
        printf("\nEnter the arrival time : ");
        scanf("%d",&p[i].at);
    }
}

// to display list of process
void display(){
    printf("\nProcess\t\tbt\tat\twt\ttat\n");
    for(int i = 1; i <= n ; i++){
        printf("\n%s",p[i].pnm);
        printf("\t%d",p[i].bt);
        printf("\t%d",p[i].at);
        printf("\t%d",p[i].wt);
        printf("\t%d",p[i].tat);
    }
    printf("\n average wait time is : %f",avg1);
    printf("\n average turn around time is : %f",avg2);
}

//sorting the process based on their arrival time for fcfs - first come first serve
void sort(){
    for(int i = 1; i <= n ; i++){
        for(int j = i + 1 ; j <= n ; j++){
            swap(i , j);
        }
    }
}

void fcfs(){
    int time = 0;
    for(int i = 1 ; i <= n ; i++){
        p[i].st = time;
        while(p[i].bt != 0){ //will run until burstime is over or until execution time(burst time) has reached
            p[i].bt--; //to make bt 0 which is amt of loop to reach 0 is equal to execution time
            time++; // time take to complete execution
        }
        p[i].ft = time; //updating process finish time of current process after execution
    }
}

//to calculate avg wt and tat
void avg(){
    int twt = 0 , ttat = 0 ; //total waiting time and turnaround time
    for(int i = 1 ; i <= n ; i++){
        p[i].wt = p[i].st - p[i].at; //waiting time = process start time - process arrival time
        p[i].tat = p[i].ft - p[i].at; //turnaround time = process finish time - process arrival time
        twt = twt + p[i].wt; // calc total waiting time
        ttat = ttat + p[i].tat; //calc total turn around time
    }
    //calculating avgs
    avg1 = (float)twt/n;
    avg2 = (float)ttat/n;
}

int main(){
    printf("\n Enter number of process : ");
    scanf("%d", &n);
    //step 1 - accept process
    accept();
    //step 2 - sort the process
    sort();
    //step 3 - perform fcfs
    fcfs();
    //step 4 - calculate averages
    avg();
    //step 5 - display result
    display();
}

