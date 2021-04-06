#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main()
{
  umask(0);
  char *fifo_name="./test.fifo";
  int ret=mkfifo(fifo_name,0664);
  if(ret<0 && errno!=EEXIST){
    perror("mkfifo error:");
    return -1;
  }

  int fd=open(fifo_name,O_WRONLY);
  if(fd<0){
    perror("open error:");
    return -1;
  }
  while(1){
    char buf[1024];
    scanf("%s",buf);
    int ret=write(fd,buf,strlen(buf));
    if(ret<0){
      perror("write error:");
      return -1;

    }
  }
  close(fd);
  return 0;
}
