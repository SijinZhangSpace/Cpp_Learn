#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <sstream>
#include <algorithm>

using namespace std;

map<string, int> dict;

int main(int argc, char *argv[])
{
    dict["test"] = 1;
    dict["abc"] = 5;

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
    //2、执行bind函数，绑定服务器的ip与端口号
    struct sockaddr_in addr;//创建sockaddr_in的变量
    memset(&addr, 0, sizeof(addr));//初始化

    //绑定服务器的ip与端口号
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    //3、执行listen函数，让服务器处于监听状态
    ret = listen(listenfd, 128);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }

    cout << "server is listening..." << endl;
    //4、执行accept函数，让服务器阻塞等待客户端的连接
#if 0
    //使用接下来几行代码接收客户端的ip与端口
    struct sockaddr_in cliAddr;
    socklen_t addrlen = sizeof(cliAddr);
    int connfd = accept(listenfd, (struct sockaddr *)&cliAddr, &addrlen);
#endif
    int connfd = accept(listenfd, nullptr, nullptr);
    if(connfd < 0)
    {
        perror("accept");
        return -1;
    }
    //5、读写数据（让客户端与服务器传输数据）
    while(1)
    {
        char buf[128] ={0};
        //服务器接收客户端的数据
        ssize_t len  = recv(connfd, buf, sizeof(buf), 0);
        if(len > 0)
        {
            cout << ">>recv client msg : " << buf << endl;
            istringstream iss(buf);
            string word;
            while(iss >> word)
            {
                cout << "in while()" << endl;
                auto it = dict.find(word);
                if(it == dict.end())
                {
                    dict.insert(pair<string, int>(word, 1));
                    cout << "New word: " << word << endl;
                }
                else
                {
                    it->second++;
                    cout << word << " is already in dict" << endl;
                }
            }
        }
        else if(0 == len)
        {
            cout << "len == 0" << endl;
        }
        else
        {
            cout << "服务器读取数据失败 " << endl;
        }

        //让服务器发送数据给客户端
        /* string line; */
        /* cin >> line; */
        /* getline(cin, line); */
        /* ssize_t len2 = send(connfd, line.c_str(), line.size(), 0); */

        istringstream iss2(buf);
        string word2;
        string opt;
        while(iss2 >> word2)
        {
            auto it = dict.find(word2);
            opt.append(word2 + " has been query for " + to_string(it->second) + " times.\n");
        }

        ssize_t len2 = send(connfd, opt.c_str(), opt.size(), 0);
        if(len2 > 0)
        {
            cout << "服务器发送数据正常" << endl;
        }
        else if(0 == len2)
        {
            cout << "服务器发送数据len2 == 0 " << endl;
        }
        else
        {
            cout << "服务器发送数据失败" << endl;
        }
    }
    //6、执行close函数，关闭文件描述符
    close(listenfd);
    close(connfd);
    return 0;
}

