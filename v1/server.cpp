#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <cstdio>
#include <errno.h>

int main() {
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
//   socket函数创建套接字
//   AF_INET: IP地址类型为IPv4 
//   SOCK_STREAM：数据传输方式为TCP
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8888);
  if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("bind err: %s\n", strerror(errno));
    close(listen_fd);
    return -1;
  }
//  bind函数绑定套接字和监听地址（IP、端口）
//  listen_fd：socket函数返回的socket描述符
//  server_addr：设置要绑定的地址信息
  if (listen(listen_fd, 2048) < 0) {
    printf("listen err: %s\n", strerror(errno));
    close(listen_fd);
    return -1;
  }
//  listen函数让套接字进入监听状态
//  2048：表示全连接队列的大小
  struct sockaddr_in client_addr;
  bzero(&client_addr, sizeof(struct sockaddr_in));
  socklen_t client_addr_len = sizeof(client_addr);
  int accept_fd = 0;
  while((accept_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len)) > 0) {
//  accept函数获取客户端请求
//  listen_fd：服务端监听的socket
//  client_addr：获取到的客户端地址信息
// accpet返回一个新的套接字，之后服务端用这个套接字与连接对应的客户端进行通信。
    printf("get accept_fd: %d from: %s:%d\n", accept_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    char read_msg[100];
    int read_num = read(accept_fd, read_msg, 100);
    printf("get msg from client: %s\n", read_msg);
    int write_num = write(accept_fd, read_msg, read_num);
    close(accept_fd);
  }
}
