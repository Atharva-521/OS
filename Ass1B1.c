#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void swap(int arr[],int i , int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

void display(int arr[], int n){
    
    for(int i = 0 ; i < n ; i++){
        printf("%d ",arr[i]);

    }
    printf("\n");
}
int main(){
    int pid;
    pid = fork();
    int arr[] = {3,7,2,8,5,1,9,6,4,10};
    int n = 10;
    if(pid > 0){
        printf("Parent proces\n");
        for(int i = 0 ; i < n - 1 ; i++){
            for(int j = 0 ; j < n - i - 1 ; j++){
                if(arr[j] > arr[j + 1]){
                    swap(arr,j,j+1);
                }
            }

        }
        printf("bubble sort : ");
        display(arr,10);
        wait(NULL);
    }
    else {
        int i , key , j;
        for(int i = 1 ; i < n ; i ++){
            key = arr[i];

            j = i - 1;
            while(j >= 0 && arr[j] > key){
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;

        }
        printf("insertion sort : ");
        display(arr,10);
    }
}