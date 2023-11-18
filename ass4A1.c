//fifo in theis we take page reference array and map it to frames array then check if the page refernnce is present in
//frames if present good else not present we count it as fault and then map or put the current pg reference to frames 
//array by hashing
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>

int nop,nof,prf[20],frame[5],pg;
// nop - no of pages
// nof - no of frames
// prf - page reference string array
// frame - array of frames frame = index and frame[index] = page means page is mapped with frame
// pg - current frame

void accept(){
    printf("Enter the no of pages : ");
    scanf("%d",&nop);
    printf("Enter the no of frames : ");
    scanf("%d",&nof);

    printf("\nENter the page reference (data) : ");
    for(int i = 1 ; i <= nop ; i++){
        scanf("%d",&prf[i]);
    }
}

void display(){
    printf("\nYour Data is : ");
    for(int i = 1 ; i <= nop ; i++){
        printf(" %d ",prf[i]);
    }
    printf("\nFrames : ");
    for(int i = 0 ; i < nof ; i++){
        printf( " %d ",frame[i]);
    }
}

//initialising frame array
void init(){
    for(int i = 0 ; i <= nof ; i++){
        frame[i] = -1;
    }
}

// now to search and return the frame(index) of current page
int searchPageInFrame(int page){
    for(int i = 0 ; i< nof ; i++){
        if(frame[i] == page){
            //if current page is there in any frame or index then return the frame or index;
            return i;
        }
        //if not found
        return -1;
    }
}

//fifo - we search frame of pages in frame array according to the arrival of pages in prf array f.ex fifo first in first out
void fifo(){
    int fault = 0, p = -1,frameIndex;
    for(int i = 1 ; i<= nop ; i++){
        //search for page line wise f.ex 1,2,3... fifo
        frameIndex = searchPageInFrame(prf[i]);
        if(frameIndex == -1){
            //if page not found in any frame then there is fault
            fault++;
            p = (p+1)%nof; //hashing p to get a index in frame array for inserting page which was not there in frame 
            frame[p] = prf[i];
            display();
            printf("\nNo of page fault : %d",fault);
        }
    }
}

//LRU code block
int pos[10]; 

int minpos(){
    //function to find the position with minimum pgref index.
    //pos array contains all the recently used page references index(k) in it
    //finding minimum frame/index from pos array means finding the lowest index of page reference(k)
    //bcz we traversed backward from current page ref index(i) towards 0th index and check if the value at current 
    //index is already present in current frame or not if value is present
    //then most likely its index will be greater than the index of pg ref containing same value bcz we traversed backward
    //and since we then updated the frame/index of old values posn's index  with new one which is most likely > old one
    //means that greater the value or index of pgref in pos array means most frequently it has arrived bcz its index is greater
    //and smaller index means its most likely not updated hence not repeated
    //so we return that small index posn
    //code
    int min = 99,index;
    for(int i = 0 ; i<nof ; i++){
        if(pos[i] < min){
            min = pos[i];
            index = i;
        }
    }
    return index;
}

    //lru - least recently used means less repeated (less touched).
    void lru(){
        int i , j , x , fault = 0 , k , flag , z;
        for(int i = 0 ; i < nop ; i++){
            flag = 0;
            x = searchPageInFrame(prf[i]);
            if(x == -1){
                //element not found in frames
                fault++;
                //to insert this page reference in frame find empty frame
                for(int j = 1 ; j <= nof ; j++){
                    if(frame[j] == -1){
                        //empty frame found
                        frame[j] = prf[i];
                        flag = 1; //empty space found
                        break;
                    }
                }
                    //No empty space for pg ref found in frame then
                    if(flag == 0){
                        //for each frames already existing value we find new recently used same value
                        //of pg ref backwards from current pg ref index(i) and update this new position of same value
                        // which is greater than old in pos arrays index.
                        for(int j = 0 ; i < nof ; j++){ //find same value with high index for current frame j
                            for(int k = i - 1 ; k >= 0 ; k--){ //iterate backwards from current pg ref posn to find same
                            //value
                            if(frame[j] == prf[k]){
                                //means if same value is fount(can be of higher index most likely or same index)
                                pos[j] = k ; //update frame to new position of pg ref 
                                break;
                            }

                            }
                        }
                    }

                z = minpos(); //finding least recentlu used pg ref (one with lower value in pos array)
                printf("\nMin pos %d",z);
                //updating the least used frame with new pg ref value
                frame[z] = prf[i];
            }
        }
        display();
        printf("\nNo of fault %d",fault);
    }


int main(){
    accept();
    init();
    display();
    // fifo();
    lru();
    display();
}