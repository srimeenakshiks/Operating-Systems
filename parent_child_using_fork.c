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
}