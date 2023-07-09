## 介绍

由于之前服务端只有一个线程，获取client套接字还有连接通信全在一个线程中。


### 多线程

考虑开多个线程。主线程只负责accept获取客户端套接字。每来一个连接，我们就新起一个线程去处理客户端和服务端的通信。这样多个连接之间就不会互相影响了。

```bash
g++ -std=c++11 per_conn_per_thread_server.cpp -lpthread -o per_conn_per_thread_server
```
弊端：

1）一个系统能同时创建的线程数量是有限的，而且线程数量越多，占用内存也会变多，容易导致OOM。

2）每个连接都用一个新线程去处理，处理结束后销毁对应线程，线程创建和销毁都需要较大开销。

3） 一个线程当执行时间片用完或者遇到系统调用阻塞时，都会让出CPU。CPU会保留线程的现场信息，然后去执行其他线程（这个过程也称为CPU上下文切换）。所以当线程数很多时，CPU的线程上下文切换也会越频繁，真正用于处理连接通信的时间也会越少。也就是CPU在瞎忙活。

### IO多路复用和Reactor模型



## 参考链接

[真正的高并发还得看IO多路复用](https://mp.weixin.qq.com/s?__biz=MzI4MTc0NDg2OQ==&mid=2247484643&idx=1&sn=541786b1cb873da7243adb58554632ad&chksm=eba5c069dcd2497f8fcf644dec68a181af89ff91642548b66ae8936e6db94cdbf362b67bcc00&scene=21#wechat_redirect)