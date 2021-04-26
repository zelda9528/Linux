#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_cond_t cond_customer;
pthread_cond_t cond_cooker;
pthread_mutex_t mutex;

int counter=0;  //柜台   等于0表示柜台上没有饭

void *cooker(void* arg){
  while(1){
    //加锁
    pthread_mutex_lock(&mutex);
    while(counter==1){
      //表示柜台上有饭，厨师不需要做饭，cooker阻塞
      pthread_cond_wait(&cond_cooker,&mutex);
    }
    //做饭
    printf("做了一碗饭！\n");
    counter++;
    //唤醒顾客
    pthread_cond_signal(&cond_customer);
    //解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
void *customer(void* arg){
  while(1){
    //加锁
    pthread_mutex_lock(&mutex);
    while(counter==0){
      //阻塞
      pthread_cond_wait(&cond_customer,&mutex);
    }
    //吃饭
    printf("吃完了，好吃！\n");
    counter--;
    //唤醒厨师
    pthread_cond_signal(&cond_cooker);
    //解锁
    pthread_mutex_unlock(&mutex);

  }
  return NULL;
}


int main(){
  pthread_t tid1,tid2;


  pthread_cond_init(&cond_customer,NULL);    //初始化条件变量
  pthread_cond_init(&cond_cooker,NULL);    //初始化条件变量
  pthread_mutex_init(&mutex,NULL);  //初始化互斥锁

  int ret=0; 
  for(int i=0;i<3;i++){
    ret=pthread_create(&tid1,NULL,cooker,NULL); //创建cooker线程
    if(ret!=0){
     printf("thread create error!\n");
     return -1;
    }
  }
  for(int i=0;i<3;i++){
    ret=pthread_create(&tid2,NULL,customer,NULL); //创建customer线程
    if(ret!=0){
     printf("thread create error!\n");
     return -1;
    }
  }
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_cond_destroy(&cond_customer);    //销毁条件变量
  pthread_cond_destroy(&cond_cooker);    //销毁条件变量
  pthread_mutex_destroy(&mutex);  //销毁互斥锁
  return 0;
}
