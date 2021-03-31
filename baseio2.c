#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
  umask(0);//将当前进程的文件权限掩码设置为0
          //避免创建文件时，权限受到影响
  //open(文件名，选项标志，操作权限)
  int fd=open("bite",O_RDWR|O_CREAT|O_APPEND,0777);
  if(fd<0)
  {
    perror("open error:");
    return -1;
  }

  char *ptr="I like Linux!\n";
  int ret= write(fd,ptr,14);
  if(ret<0)
  {
    perror("write error:");
    return -1;
  }
  
  //lseek(句柄，偏移量，偏移起始位置)
  lseek(fd,0,SEEK_SET);


  char buf[1024]={0};
  ret=read(fd,buf,1023);
  if(ret<0)
  {
    perror("read error:");
    return -1;
  }
  printf("%d-%s\n",ret,buf);



  close(fd);
  return 0;
}
