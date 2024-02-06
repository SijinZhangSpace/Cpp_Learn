#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

list<string> dict;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout << "argc < 3" << endl;
        return -1;
    }
    //1、调用socket函数，创建文件描述符
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        perror("socket");
        return -1;
    }
    //2、执行connect函数，绑定服务器的ip与端口号，进行与服务器连接
    struct sockaddr_in addr;//创建sockaddr_in的变量
    memset(&addr, 0, sizeof(addr));//初始化

    //绑定服务器的ip与端口号
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("connect");
        return -1;
    }
    
    //3、读写数据（让客户端与服务器传输数据）
    while(1)
    {
        //让客户端发送数据给服务器
        string line;
        /* cin >> line; */
        getline(cin, line);
        /* istringstream iss(line); */
        /* string word; */
        /* while(iss >> word) */
        /* { */
        /*     auto it = find(dict.begin(), dict.end(), word); */
        /*     if(it != dict.end()) */
        /*     { */
        /*         cout << word << " is already in the dict" << endl; */
        /*     } */
        /*     else */
        /*     { */
        /*         dict.push_back(word); */
        /*         cout << word << "is pushed in to the dict" << endl; */
        /*     } */
        /* } */
        ssize_t len = send(listenfd, line.c_str(), line.size(), 0);
        if(len > 0)
        {
            cout << "客户端发送数据正常" << endl;
        }
        else if(0 == len)
        {
            cout << "客户端发送数据len == 0 " << endl;
        }
        else
        {
            cout << "客户端发送数据失败" << endl;
        }

        char buf[128] ={0};
        //客户端接收服务器的数据
        ssize_t len2  = recv(listenfd, buf, sizeof(buf), 0);
        if(len2 > 0)
        {
            cout << ">>recv server msg : " << buf << endl;
        }
        else if(0 == len2)
        {
            cout << "客户端接收数据len2 == 0" << endl;
        }
        else
        {
            cout << "客户端读取数据失败 " << endl;
        }

    }
    
    //4、执行close函数，关闭文件描述符
    close(listenfd);
    return 0;
}

