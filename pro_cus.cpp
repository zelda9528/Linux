#include<cstdio>
#include<queue>
#include<iostream>
#include<pthread.h>
#include<unistd.h>

class BlockQueu{
  private:
    int capacity;
    std::queue<int> _queue;
    pthread_mutex_t mutex;
    pthread_cond_t pro_cond;
    pthread_cond_t cus_cond;

    
  public:
    BlockQueu(int cap=5):capacity(cap)
    {
      pthread_mutex_init(&mutex,NULL);
      pthread_cond_init(&pro_cond,NULL);
      pthread_cond_init(&cus_cond,NULL);
    }
    
   bool Push(int data)
    {
      pthread_mutex_lock(&mutex);
      while((int)_queue.size()==capacity)
      {
        pthread_cond_wait(&pro_cond,&mutex);
      }
      _queue.push(data);

      pthread_cond_signal(&cus_cond);
      pthread_mutex_unlock(&mutex);
      return true;
    }

    bool Pop(int *data)
    {
      pthread_mutex_lock(&mutex);
      while(_queue.empty())
      {
        pthread_cond_wait(&cus_cond,&mutex);
      }

      *data=_queue.front();
      _queue.pop();

      pthread_cond_signal(&pro_cond);
      pthread_mutex_unlock(&mutex);

      return true;
    }

    ~BlockQueu()
    {
      pthread_mutex_destroy(&mutex);
      pthread_cond_destroy(&pro_cond);
      pthread_cond_destroy(&cus_cond);
    }

};


void* productor(void * arg){
  BlockQueu* q=(BlockQueu*)arg;
  int i=0;
  while(1){
    q->Push(i);
    printf("生产者入队数据：%d\n",i++);
  }
  return NULL;
}
void* customer(void * arg){
  BlockQueu* q=(BlockQueu*)arg;
  while(1){
    int data;
    q->Pop(&data);
    printf("消费者出队数据：%d\n",data);
  }
  return NULL;
}

int main()
{
  BlockQueu q;
  pthread_t pid[4],cid[4];
  int ret=0;
  for(int i=0;i<4;i++){
    ret=pthread_create(&pid[i],NULL,productor,&q);
    if(ret!=0){
      printf("create error!\n");
      return -1;
    }
  }

  for(int i=0;i<4;i++){
    ret=pthread_create(&cid[i],NULL,customer,&q);
    if(ret!=0){
      printf("create error!\n");
      return -1;
    }
  }
  
  for(int i=0;i<4;i++){
    pthread_join(pid[i],NULL);
    pthread_join(cid[i],NULL);

  }

  return 0;
}

