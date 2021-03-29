#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
  int pid=fork();
  if(pid<0)
  {
    //出错
    perror("fork error");
    return -1;
  }
  else if(pid==0)
  {
    //子进程
    sleep(5);
    return 99;//main中的return--退出子进程，退出返回值为99
  }
  
 // int ret=wait(NULL);
 // printf("progress:%d exit\n",ret);
  int ret,status; 
  while((ret=waitpid(-1,&status,WNOHANG))==0)
    {
      //非阻塞状态下，没有子进程退出，返回0
      printf("当前子进程还没有退出\n");
      sleep(1);
    }
    if(ret<0)
    {
      perror("waitpid error:");
    }
    if((status & 0x7f)!=0)
    {
      printf("进程异常退出！");
      return -1;
    }
    int retval=(status>>8)&0xff;
    printf("%d-%d exit-retval:%d\n",ret,pid,retval);
 //父进程
    while(1)
    {
      sleep(1);//死循环
    }
  return 0;
  
}
