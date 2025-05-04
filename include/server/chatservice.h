#ifndef CHATSERIVCE_H_
#define CHATSERIVCE_H_

#include <unordered_map>
#include <functional>
#include "json.hpp"
#include <muduo/net/TcpConnection.h>
#include <memory>
#include "UserModel.h"
#include "offlinemessagemodel.h"
#include <mutex>
#include "friendmodel.h"
#include "groupmodel.h"
#include "redis.h"




using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

//表示处理消息的事件回调类型
using MsgHandler = std::function<void(const TcpConnectionPtr & conn, json & js, Timestamp time)>;

//主要是做业务
//聊天服务器业务类
class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService * instance();
    // 处理登录业务
    void login(const TcpConnectionPtr & conn, json & js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr & conn, json & js, Timestamp time);

    //一对一聊天业务
    void oneChat(const TcpConnectionPtr & conn, json & js, Timestamp time);

    //创建群组业务
    void createGroup(const TcpConnectionPtr & conn, json & js, Timestamp time);

    //加入群组业务
    void addGroup(const TcpConnectionPtr & conn, json & js, Timestamp time);

    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);


    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);


    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr & conn);

    //服务器异常，业务充值方法
    void reset();

    //添加好友业务
    void addFriend(const TcpConnectionPtr & conn, json & js, Timestamp time);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    void handleRedisSubscribeMessage(int userid, string msg);
private:

    ChatService();
    //存储消息id对应的处理操作
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 数据操作类对象
    UserModel _userModel;

    //
    offlineMsgModel _offlineMsgModel;
    //
    Friendmodel _friendModel;
    GroupModel _groupModel;

    //存储在线用户的通信链接(需要考虑线程安全的问题)
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    //int类型保存的是id

    //定义互斥锁,保证_userConnMap的线程安全
    mutex _connMutex;

    //redis操作对象
    Redis _redis;

};



#endif
