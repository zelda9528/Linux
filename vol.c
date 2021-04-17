#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

volatile int a=1;
void sigcb(int no){
  a=0;
  printf("a=%d\n",a);
}
int main(){
  signal(SIGINT,sigcb);
  while(a){

  }
  printf("程序正常结束\n");
  return 0;
}
