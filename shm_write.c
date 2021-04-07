
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#define IPC_KEY 0x0123456

int main(){

  //创建共享内存
  //shmget(标识符，大小，打开方式和权限)
  int shmid=shmget(IPC_KEY,32,IPC_CREAT|0664);
  if(shmid<0){
    perror("shmget error:");
    return -1;

  }
  
  void * shm_start=shmat(shmid,NULL,0);
  if(shm_start==(void*)-1){
    perror("shmat error:");
    return -1;
  }
  
  int i=0;
  while(1){
    //sprintf--将格式化后的字符串放到指定的内存空间中
    sprintf(shm_start,"好好学习，天天向上！-%d",i++);
    sleep(1);
  }
  shmdt(shm_start);
  shmctl(shmid,IPC_RMID,NULL);


  return 0;
}
