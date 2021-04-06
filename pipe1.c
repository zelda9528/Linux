#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  int pipefd[2];
  int ret=pipe(pipefd);       //创建管道
  if(ret <0)
  {
    perror("pipe error:");
    return -1;
  }
  pid_t pid=fork();           //创建子进程
  if(pid<0)
  {
    perror("fork error");
    exit(-1);
  }
  else if(pid == 0)
  {
    //child
    close(pipefd[1]);         //关闭写端
    sleep(1);               
    char buf[1024]={0};
    int ret=read(pipefd[0],buf,1023);
    if(ret<0)
    {
      perror("read error:");
      return -1;
    }
    else if(ret==0)
    {
      printf("all write closed!\n");
    }
    printf("buf:%s\n",buf);
  }
  else
  {
    //parent
    close(pipefd[1]);         //关闭写端
    sleep(100);               //关闭后续的写端---write
    char*ptr="中午吃啥?\n";
    int ret=write(pipefd[1],ptr,strlen(ptr));
    if(ret<0)
    {
      perror("write error:");
      return -1;
    }
    printf("写入成功\n");
  }
  return 0;
}
