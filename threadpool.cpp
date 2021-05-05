#include<queue>
#include<pthread.h>
#include<cstdio>
#include<unistd.h>

typedef void (*handler_t)(int data);
class ThreadTask{
  private:
    int data_;
    handler_t handler_;
  public:
    ThreadTask(){}
    ThreadTask(int data,handler_t handler):data_(data),handler_(handler)
    {}

    void Run(){
      handler_(data_);
    }
};

class BlockQueue{
  private:
    int capacity;               //容量
    std::queue<ThreadTask> _queue;     //底层封装一个队列
    pthread_mutex_t mutex;      //互斥锁
    pthread_cond_t cond_pro;    //生产者条件变量
    pthread_cond_t cond_cus;    //消费者条件变量
  public:

    BlockQueue(int cap=5):capacity(cap){
      pthread_mutex_init(&mutex,NULL);
      pthread_cond_init(&cond_pro,NULL);
      pthread_cond_init(&cond_cus,NULL);
    }

    bool Push(ThreadTask &data){
      pthread_mutex_lock(&mutex);
      while((int)_queue.size()==capacity){
        pthread_cond_wait(&cond_pro,&mutex);
      }
      _queue.push(data);
      pthread_cond_signal(&cond_cus);
      pthread_mutex_unlock(&mutex);
      return true;
    }

    bool Pop(ThreadTask* data){
      pthread_mutex_lock(&mutex);
      while(_queue.empty()){
        pthread_cond_wait(&cond_cus,&mutex);
      }
      *data=_queue.front();
      _queue.pop();
      pthread_cond_signal(&cond_pro);
      pthread_mutex_unlock(&mutex);
      return true;
    } 

    ~BlockQueue(){
      pthread_mutex_destroy(&mutex);
      pthread_cond_destroy(&cond_pro);
      pthread_cond_destroy(&cond_cus);
    }              
};


class ThreadPool{
  private:
    int max_thread;
    int max_queue;
    BlockQueue queue_;
  
  static void* entry(void *arg){
    ThreadPool *pool=(ThreadPool*)arg;
    while(1){
      ThreadTask task;
      pool->queue_.Pop(&task);
      task.Run();
    }
      return NULL;
    }

  public:
    ThreadPool(int thread=5,int queue=10):max_thread(thread),max_queue(queue),queue_(queue){
    int ret;
    pthread_t tid;
      for(int i=0;i<thread;i++){
        ret=pthread_create(&tid,NULL,entry,this);
        if(ret!=0){
          printf("create thread error\n");
          _exit(-1);
        }
        pthread_detach(tid);
    }
  }
    bool TaskPush(ThreadTask &task)
    {
      queue_.Push(task);
      return true;
    }
    bool Init(){

      return true;
    }

};

void test(int data){
  printf("i am thr:%p--get data:%d,will sleep: %d s\n",pthread_self(),data,data%5);
  sleep(data%5);
}

int main(){

  ThreadPool pool;
  for(int i=0;i<10;i++){
    ThreadTask task(i,test);
    pool.TaskPush(task);
  }
  while(1)sleep(1);
  return 0;
}
