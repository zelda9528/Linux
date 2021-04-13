#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main()
{
  mkfifo("test.fifo",0664);

  int fd=open("test.fifo",O_RDONLY);
  
  char  buf[1024]={0};

  read(fd,buf,1023);

  printf("buf:%s\n",buf);

  return 0;
}
