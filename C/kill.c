#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
 pid_t pid,pid2;
 if (( pid = fork()) == 0) {
   while(1) {
     printf("HIJO PID = %d, getpid()=%d, getppid()=%d\n", pid,getpid(),getppid());
     sleep(1);
   }
 }
 if (( pid2 = fork()) == 0) {
   while(1) {
     printf("HIJO PID = %d, getpid()=%d, getppid()=%d\n", pid2,getpid(),getppid());
     sleep(1);
   }
 }

 sleep(60);
 printf("PADRE Terminacion proceso %d\n", pid);
 kill (pid,SIGKILL);

 sleep(60);
 printf("PADRE Terminacion proceso %d\n", pid2);
 kill (pid2,SIGKILL);

 exit(0);
}

