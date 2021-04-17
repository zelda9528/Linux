#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sigcd(int no)
{
  printf("吃饭不？\n");
  printf("吃个der！\n");
  alarm(3);
}

int main()
{
  alarm(3);
  signal(SIGALRM,sigcd);
  while(1){
      printf("学习！学习！学习！\n");
      sleep(1);
  }
  return 0;
}
