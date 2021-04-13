#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#define IPC_KEY 0x0123456

int main(){

  int shmid=shmget(IPC_KEY,32,IPC_CREAT|0664);
  void* shm_start=shmat(shmid,NULL,0);
  int i=0;
  while(1)
  {
    sprintf(shm_start,"你真帅--%d",i++);
    sleep(1);
  }

  shmdt(shm_start);
  shmctl(shmid,IPC_RMID,NULL);


  return 0;
}
