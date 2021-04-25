#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int tickets=100;
void* scalpers(void* arg){
  pthread_mutex_t* mutex=(pthread_mutex_t*)arg;
  pthread_t tid=pthread_self();
  while(1){
    pthread_mutex_lock(mutex);    //加锁
    if(tickets>0){
      usleep(1);
      printf("I got a ticket!-%p-%d\n",tid,tickets);
      tickets--;
      pthread_mutex_unlock(mutex);  //解锁
    }else{
      pthread_mutex_unlock(mutex);  //在任意有可能造成线程退出的地方都要进行解锁
      pthread_exit(NULL);
    }
  }
  return NULL;
}

int main(){
  pthread_mutex_t mutex;
  pthread_t tid[4]={0};
  int ret=0;

  pthread_mutex_init(&mutex,NULL);  //互斥锁的初始化必须在线程创建之前
  for(int i=0;i<4;i++)
  {
    ret=pthread_create(&tid[i],NULL,scalpers,&mutex);
    if(ret!=0){
      printf("pthread_create error\n");
      return -1;
    }
  }
  
  for(int i=0;i<4;i++){
    pthread_join(tid[i],NULL);
  }

  pthread_mutex_destroy(&mutex);  //销毁互斥锁
  
  return 0;
}
