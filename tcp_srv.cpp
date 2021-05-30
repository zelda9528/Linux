#include "tcpsocket.hpp"

int main(int argc,char* argv[]){
 
  //命令行： ./tcp_srv 192.168.2.2   9000
  if(argc!=3){
    printf("格式：./tcp_src 192.168.2.2 9000\n");
    return -1;
  }

  std::string srvip=argv[1];
  uint16_t srvport=std::stoi(argv[2]);
  TcpSocket lst_sock;//监听套接字，仅用于接受新连接
  //1.创建套接字
  CHECK_RET(lst_sock.Socket());
  //2.绑定地址信息
  CHECK_RET(lst_sock.Bind(srvip,srvport));
  //3.开始监听
  CHECK_RET(lst_sock.Listen());
  while(1){
    //4.获取新连接
   TcpSocket cli_sock;//客户端套接字
   std::string cli_ip;//客户端ip地址
   uint16_t cli_port; //客户端端口
   bool ret=lst_sock.Accept(&cli_sock,&cli_ip,&cli_port);
   if(ret==false){
     //客户端发生错误，服务端不能退出，继续处理下一个客户端的请求
     continue;
   }
   std::cout<<"获取新建连接："<<cli_ip<<":"<<cli_port<<std::endl;
   //5.收发数据---使用获取的新建套接字进行通信
   std::string buf;
   ret=cli_sock.Recv(&buf);
   if(ret==false){
     cli_sock.Close();
     continue;
   }
   std::cout<<"client say:"<<buf<<std::endl;
   buf.clear();
   std::cout<<"server say:";
   std::cin>>buf;
   ret=cli_sock.Send(buf);
  
   if(ret==false){
     cli_sock.Close();
   }

  }
  //6.关闭套接字
  lst_sock.Close();
  return 0;
}
