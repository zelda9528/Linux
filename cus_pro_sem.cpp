#include<vector>
#include<iostream>
#include<semaphore.h>
#include<cstdio>
#include<pthread.h>

class RingQueue{
  private:
    int _capacity;            //容量
    std::vector<int> _arry;   //封装一个vector
    int _read;                //读索引
    int _write;               //写索引
    sem_t sem_lock;           //用于实现互斥的信号量
    sem_t sem_idle;           //记录空闲节点的信号量
    sem_t sem_data;           //记录数据节点的信号量
  public:
    RingQueue(int cap=5):_capacity(cap),_arry(cap),_read(0),_write(0)
  {
    sem_init(&sem_lock,0,1);
    sem_init(&sem_idle,0,cap);
    sem_init(&sem_data,0,0);

  }

    bool Push(int data){
      sem_wait(&sem_idle);    //判断是否有空结点可供插入，没有则阻塞
      sem_wait(&sem_lock);    //加锁

      _arry[_write]=data;
      _write=(_write+1)%_capacity;

      sem_post(&sem_lock);    //解锁
      sem_post(&sem_data);    //数据结点+1，唤醒消费者
      return true;
    }
    bool Pop(int* data){
      sem_wait(&sem_data);    //判断是否有数据节点可供处理，没有则阻塞
      sem_wait(&sem_lock);    //加锁

      *data=_arry[_read];
      _read=(_read+1)%_capacity;

      sem_post(&sem_lock);    //解锁
      sem_post(&sem_idle);    //空结点+1，唤醒生产者
      return true;
    }

    ~RingQueue(){
      sem_destroy(&sem_lock);
      sem_destroy(&sem_idle);
      sem_destroy(&sem_data);
    }

};


void* productor(void* arg){
  RingQueue* q=(RingQueue*)arg;
  int i=0;
  while(1){
    q->Push(i);
    printf("生产者入队数据：%d\n",i++);

  }
  return NULL;

}
void* customer(void* arg){
  RingQueue* q=(RingQueue*)arg;
  while(1){
    int data;
    q->Pop(&data);
    printf("消费者出队数据：%d\n",data);

  }
  return NULL;

}

int main(){
  RingQueue q;
  pthread_t ptid[4],ctid[4];
  int ret;
  for(int i=0;i<4;i++){
    ret=pthread_create(&ptid[i],NULL,productor,&q);
    if(ret!=0){
      printf("create thread error\n");
      return -1;
    }
  } 

  for(int i=0;i<4;i++){
    ret=pthread_create(&ctid[i],NULL,customer,&q);
    if(ret!=0){
      printf("create thread error\n");
      return -1;
    }
  }

  for(int i=0;i<4;i++){
    pthread_join(ptid[i],NULL);
    pthread_join(ctid[i],NULL);
  }
  return 0;
}


