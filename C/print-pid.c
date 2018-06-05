#include<stdio.h>
#include<unistd.h>

main()
{
  printf("El process id es %d\n", getpid());
  printf("El parent process id es %d\n", getppid());
}
