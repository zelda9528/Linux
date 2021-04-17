#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void sigcb(int no)
{
  printf("recv signal:%d\n",no);
}

int main(){
  signal(SIGINT,sigcb);
  signal(40,sigcb);
  sigset_t set;//定义一个阻塞集合
  sigemptyset(&set);//清空
  sigfillset(&set);//填充

  sigprocmask(SIG_BLOCK,&set,NULL);
  printf("信号全部阻塞！输入回车继续执行：");
  getchar();
  sigprocmask(SIG_UNBLOCK,&set,NULL);

  while(1)sleep(1);

  return 0;
}
