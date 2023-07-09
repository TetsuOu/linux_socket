## 执行

```bash
g++ client.cpp -o client
g++ server.cpp -o server
```

## 思考


> 先启动server，然后启动一个client，不输入数据，这个时候在另外一个终端上再启动一个client，并在第二个client终端中输入数据，会发生什么呢？


在第二个client输入后，服务端并没有响应，直到第一个client也输入数据完成交互后，第二个client才会有数据返回。这是由于服务端accept获取到第一个client的套接字后，由于第一个client未输入数据，所以服务端进程会阻塞在等待客户端数据那一行。

## 参考连接

[从一个基础的socket服务说起](https://mp.weixin.qq.com/s?__biz=MzI4MTc0NDg2OQ==&mid=2247484613&idx=1&sn=52e727e5ba69d76ea1ed1782d9f4c5be&chksm=eba5c04fdcd249590d45a41bf0842c4eb4b65b19ff41b62b94ff58df3522bf0b9b118f351f51&token=645144944&lang=zh_CN&scene=21#wechat_redirect)