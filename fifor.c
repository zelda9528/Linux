#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main(){
  umask(0);
  mkfifo("test.fifo",0664);

  char * ptr=" 你真行!";
  
  int fd=open("test.fifo",O_RDWR);
  write(fd,ptr,strlen(ptr));
  
  return 0;
}
