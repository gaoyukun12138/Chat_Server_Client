#ifndef FRIENDMODEL_H_
#define FRIENDMODEL_H_

#include "user.h"
#include <vector>
using namespace std;

//维护好友信息的操作接口方法
class Friendmodel
{
public:
    //添加好友关系
    void insert(int userid, int friendid);

    //返回用户好友列表  friendid + friend信息
    vector<User> query(int userid);

};



#endif