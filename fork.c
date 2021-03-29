#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
  pid_t pid=fork();
  //子进程复制了父进程，所以后面的代码父子进程都会有，但是返回值不同，执行的判断语句也不同
  if(pid<0)
  {
    //出错
  }
  else if(pid==0)
  {
    //子进程--返回值为0
    //sleep(5);
    //exit(0);//退出进程，谁调用退出谁
  }
  else
  {
    //父进程--返回值为子进程的pid，大于0
    sleep(5);
    exit(0);
  }
  printf("赚大钱 %d\n",getpid());
  while(1) sleep(1);
  return 0;
}
