#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
int full=0;
int empty=10;
int buffer[10];
int Flag[2];
int turn;
int front=0;
int rear=0;
int s=1;
void * consumer(){
    while(s==1){
    	sleep(0.5);
        Flag[1]=1;
        turn=1;
        while(Flag[0]==1 && turn==1);
        printf("Consumed %d\n",buffer[front]);
        front=(front+1)%10;
        empty++;
        Flag[1]=0;
    }
    return NULL;
}
int main() {
    pthread_t t;
    pthread_create(&t,NULL,
consumer,NULL);
    while(s==1){
        Flag[0]=1;
        turn=2;
        while(Flag[1]==1 && turn==2);
        printf("Enter number: ");
        scanf("%d",&buffer[rear]);
        printf("Produced %d\n",buffer[rear]);
        rear=(rear+1)%10;
        full++;
        empty--;
        Flag[0]=0;
        printf("Do you want to continue?(Yes=1;No=0): ");
        scanf("%d",&s);
       	}
    return 0;
}

