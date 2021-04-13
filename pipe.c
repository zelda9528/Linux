#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
  int pipefd[2]={0};
  pipe(pipefd);
  int pid=fork();
  if(pid<0)
  {
    perror("fork error:");
    return -1;
  }
  else if(pid==0){
    //child
    char buf[1024]={0};
    read(pipefd[0],buf,1023);
    printf("buf:%s\n",buf);
  }
  else {
    //parent
    char* str="你好帅！";
    write(pipefd[1],str,strlen(str));
    printf("写入成功！\n");
  }
  return 0;
}

