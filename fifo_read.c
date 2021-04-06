#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
  umask(0);
  char *fifo_name="./test.fifo";
  int ret=mkfifo(fifo_name,0664);
  if(ret<0 && errno!=EEXIST)
  {
    perror("mkfifo error:");
    return -1;
  }

  //open(文件名，打开方式，权限)
  int fd=open(fifo_name,O_RDONLY);
  if(fd<0){
    perror("open error:");
    return -1;
  }
  printf("open fifo success\n");
  while(1){
    char buf[1024]={0};
    int ret=read(fd,buf,1023);
    if(ret<0){
      perror("read error:");
      return -1;
    }else if(ret==0){
      printf("all write closed\n");
      return -1;
    }
    printf("buf:%s\n",buf);
  }
  close(fd);
  return 0;
}
