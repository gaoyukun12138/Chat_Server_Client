#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;



//json可以和容器直接的序列化和反序列化
/*
//json序列化示例1
void fun1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;

}


// json序列化示例2
void fun2()
{
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"] ["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    //上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    cout << js << endl;
}


// json序列化示例代码3
void fun3()
{
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    js["list"] = vec;

    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    //转成数组的元素
    js["path"] = m;

    //发送数据
    string sendbuf = js.dump();
    //json对象 序列化为 字符串

    cout << js << endl;
}
*/

//json反序列化
string fun1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump();
    return sendBuf;

}


int main()
{
    string recvBuf = fun1();
    // 数据的反序列化， json字符串 反序列化为 数据对象
    json jsbuf = json::parse(recvBuf);

    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    
    return 0;
}