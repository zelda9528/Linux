#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>



void *thr_entry(void* arg){
  //sleep(5);
  //pthread_exit(NULL);
  while(1){
    printf("normal thread--%s\n",(void*)arg);
    sleep(1);
  }
  return NULL;
}

int main(){
  //pthread_create(tid, 线程属性, 入口函数, 参数 )
  pthread_t tid;
  char *ptr="好好学习~";
  int ret=pthread_create(&tid,NULL,thr_entry,(void*)ptr);
  if(ret!=0){
    printf("thread_create error!");
    return -1;
  }
  sleep(3);
  pthread_cancel(tid);
  while(1){
    printf("天气真好\n");
    sleep(1);
  }


  return 0;
}
