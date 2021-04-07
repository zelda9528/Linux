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
  
  //与进程建立映射关系
  //shmat(操作句柄，映射首地址，访问方式)
  void * shm_start=shmat(shmid,NULL,0);
  if(shm_start==(void*)-1){
    perror("shmat error:");
    return -1;
  }
  while(1){
    printf("%s\n",(char *)shm_start);
    sleep(1);
  }

  //解除与进程的映射关系
  shmdt(shm_start);
  
  //删除共享内存
  //shmctl(操作句柄，操作类型，信息结构)
  shmctl(shmid,IPC_RMID,NULL);
  return 0;
}


