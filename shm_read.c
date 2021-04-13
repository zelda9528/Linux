#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>

#define IPC_KEY 0x123456

int main(){

  int shmid= shmget(IPC_KEY,32,IPC_CREAT|0664);
  void * shm_start=shmat(shmid,NULL,SHM_RDONLY);

  while(1)
  {
    printf("%s\n",(char *)shm_start);
    sleep(1);
  }

  shmdt(shm_start);
  shmctl(shmid,IPC_RMID,NULL);

  return 0;
}
