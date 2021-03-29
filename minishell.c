#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>

int main()
{
  while(1)
  {
    printf("dev用户输入：");
    fflush(stdout);
    char cmd[1024]={0};
    fgets(cmd,1023,stdin);
    cmd[strlen(cmd)-1]='\0';
    printf("cmd:[%s]\n",cmd);

    char* ptr=cmd;
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
     execvp(arg[0],arg);
     exit(-1);
   }
  wait(NULL);
  }
  return 0;
}
