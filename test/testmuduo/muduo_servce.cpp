/*
muduo网络库给用户提供两个类：
TCPServer: 用于编写服务器程序
TCPClient: 用于编写客户端程序

epoll + 线程池
优点： 能够把网络I/O的代码和业务代码区分
                          用户的链接和断开  用户的可读写事件
*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

// 基于muduo网络库开发服务器的程序
// 1. 组合TcpServer对象
// 2. 创建EventLoop事件循环对象的指针
// 3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
// 4. 在当前服务器类的构造函数中，注册处理链接的回调函数和处理读写事件的回调函数
// 5. 设置合适的服务端线程数量，muduo库会自己分配I/O线程和worker线程

class ChatServer
{
public:
    ChatServer(EventLoop* loop, // 事件循环 reactor
        const InetAddress& listenAddr, // IP+Port
        const string& nameArg ) // 服务器的名字
        : _server(loop, listenAddr, nameArg),
        _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调、
        // 回调：事情什么时候发生和事情发生之后怎么办不在同一时间发生

        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        //给服务器注册用户读写时间回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        //设置服务器端的线程数量 1个I/O线程，3个work线程
        _server.setThreadNum(4);
    }

    void start()
    {
        _server.start();
    }



private:

    //专门处理用户的链接创建和断开  epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn)
    {
        
        if ( conn->connected() )
        {
            cout << conn->peerAddress().toIpPort() << " -> " <<
            conn->localAddress().toIpPort() << " state:online" << endl;
            
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " <<
            conn->localAddress().toIpPort() << " state:offline" << endl;
            conn->shutdown();
           //_loop->quit(); 连接断开，资源回收
        }
    } 
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr& conn, //链接
                 Buffer* buffer,  // 缓冲区
                Timestamp time) //接收数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data: " << buf << " time:" << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server; //#1
    EventLoop * _loop; //#2 相当于epoll 用于关闭服务器
};

int main()
{
    EventLoop loop; //创建epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "Chatserver");

    server.start(); //启动服务，listenfd 通过epoll_ctl => epoll
    loop.loop(); //epoll_wait()以阻塞方式等待新用户的链接，已连接用户的读写事件等


    return 0;
}