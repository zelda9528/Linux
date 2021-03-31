#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
  while(1)
  {
    printf("dev用户输入：");
    fflush(stdout);
    char cmd[1024]={0};
    fgets(cmd,1023,stdin);
    cmd[strlen(cmd)-1]='\0';
    
    int flag=0;//定义一个重定向的标志：0-没有；1-清空；2-追加
    char* ptr=cmd;
    char* redirect_file=NULL;   //文件名起始
    while(*ptr!='\0')
    {
      if(*ptr=='>')
      {
        flag=1;
        *ptr='\0';
        if(*ptr=='>')
        {
          flag=2;
          *ptr='\0';
          ptr++;
        }

          while(*ptr!='\0'&&*ptr==' ')ptr++;
          redirect_file=ptr;
          while(*ptr!='\0'&&*ptr!=' ')ptr++;
          *ptr='\0';
      }
      ptr++;
    }

    ptr=cmd;
    char* arg[32]={NULL};
    int my_argc=0;
    while(*ptr!='\0')
    {
      if(!isspace(*ptr))
      {
        arg[my_argc]=ptr;
        my_argc++;
        while(*ptr!='\0'&&!isspace(*ptr))
        {
          ptr++;
        }
        *ptr='\0';
      }
      ptr++;
    }
   arg[my_argc]=NULL;

  pid_t pid=fork();
   if(pid<0)
   {
      perror("fork error:");
      continue;
   }else if(pid==0){
     if(flag==1)
     {
       int fd;
       fd=open(redirect_file,O_CREAT|O_RDWR|O_TRUNC,0774);
           dup2(fd,1);
     }
     else if(flag==2)
     {
      int fd;
        fd=open(redirect_file,O_CREAT|O_RDWR|O_APPEND,0774);
        dup2(fd,1);
     }
     execvp(arg[0],arg);
     exit(-1);
   }
  wait(NULL);
  }
  return 0;
}
