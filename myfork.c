#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  pid_t pid=fork();
  if(pid<0)
  {
    printf("fork error");
  }
  else if(pid==0)
  {
    while(1)
    {
      printf("child \n");
      sleep(5);
    }
  }
  while(1)
  {
    printf("father \n");
    sleep(5);
  }
  return 0;
}
