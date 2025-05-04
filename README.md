# Chat_Server_Client
可以工作在nginx负载均衡环境中的集群聊天服务器和客户端源码 基于muduo、redis、mysql实现

编译方式：
cd build
rm -rf *
cmake ..
make

需要nginx中的tcp负载均衡
