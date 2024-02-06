#ifndef __RSSREADER_H__
#define __RSSREADER_H__

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include "tinyxml2.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

struct RssItem {
    string _title;
    string _link;
    string _description;
    string _content;
};

class RssReader{
public:
    //RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
    string filter(string &str); //过滤html标签
private:
    vector<RssItem> _rss;
};

#endif
