#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>//字节序转换接口头文件
#include<netinet/in.h>//地址结构/协议类型头文件
#include<sys/socket.h>//套接字接口文件


int main()
{
  //1.创建套接字
  //int socket(地址域类型，套接字类型，协议类型);
  int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  if(sockfd<0)
  {
    perror("socket error:");
    return -1;
  }
  //2.为套接字绑定地址信息
  //int bind(操作句柄，地址结构信息，地址长度);
  struct sockaddr_in addr;//定义ipv4地址结构
  addr.sin_family=AF_INET;
  addr.sin_port=htons(9000);//设置端口
  addr.sin_addr.s_addr=inet_addr("192.168.85.128");
  int len=sizeof(addr);
  int ret=bind(sockfd,(struct sockaddr*)&addr,len);
  if(ret<0)
  {
    perror("bind error:");
      return -1;
  }
  while(1)
  {  
    //3.接收数据
    //recvfrom(句柄，空间，长度,标志，对端地址，地址长度)
    char* buf[1024]={0};
    struct sockaddr_in paddr;
    int len=sizeof(struct sockaddr_in);
    ret=recvfrom(sockfd,buf,1023,0,(struct sockaddr*)&paddr,&len);
    if(ret<0)
    {
      perror("recv error:");
        return -1;
    }
    printf("client say:%s\n",buf);
    //4.回复数据
    char* data="干饭了干饭了~~";
    ret=sendto(sockfd,data,strlen(data),0,(struct sockaddr*)&paddr,len);
    if(ret<0)
    {
      perror("send error:");
      return -1;
    }
  }
  //5.关闭套接字
  close(sockfd);
  return 0;
}


