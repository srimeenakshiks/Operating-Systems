rogram 1 (code):
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void main()
{
    int p;
    p = fork();
    //child process
    if (p==0) {
   	 for(int i = 0; i <= 20; i++) {
   		 if (i%2==0) {
   			 printf("%d ----- %d \n", getpid(), i);
   			 sleep(2);
   		 }
   	 }
    }
    //parent process
    else if (p>0) {
   	 sleep(1);
   	 for (int j = 0; j <= 20; j++) {
   		 if (j%2==1) {
   			 printf("%d ----- %d \n", getpid(), j);
   			 sleep(2);
   		 }
   	 }
    }
}#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


void *child_thread(void *arg) {
    for (int i = 0; i <= 20; i += 2) {
        printf("%ld----%d\n", pthread_self(), i);
        sleep(2);
    }
    pthread_exit(NULL);
}


void *parent_thread(void *arg) {
    sleep(1); // Ensure the child thread starts first
    for (int j = 1; j <= 20; j += 2) {
        printf("%ld----%d\n", pthread_self(), j);
        sleep(2);
    }
    pthread_exit(NULL);
}


int main() {
    pthread_t parent, child;


    pthread_create(&child, NULL, child_thread, NULL);


    pthread_create(&parent, NULL, parent_thread, NULL);


    pthread_join(child, NULL);
    pthread_join(parent, NULL);


    return 0;
}