#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
  pid_t pid=fork();
  if(pid<0)
  {
  //pid<0表示出错
     perror("fork error:");
  }
  perror("fork error");
  return 0;
}
