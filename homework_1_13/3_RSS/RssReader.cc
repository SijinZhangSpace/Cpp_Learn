#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include "tinyxml2.h"
#include "RssReader.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::regex;
using std::string;
using std::vector;
using std::ofstream;
using namespace tinyxml2;

string RssReader::filter(string &str) {
    regex reg("<[^>]*>"); //html标签的正则表达式
    return regex_replace(str, reg, "");
}

void RssReader::parseRss() {
    XMLDocument xml; //xml类
    XMLError ret = xml.LoadFile("coolshell.xml");
	if (ret != 0) {
        cout << "Fail to load xml file" << endl;
        return;
	}
    XMLElement *root = xml.RootElement(); //xml文件的根节点
    XMLElement *channel = root->FirstChildElement("channel"); //channel结点
    XMLElement *item = channel->FirstChildElement("item"); //item结点

    while(item) {
        RssItem rss_it;
        
        for(XMLElement *current_element = item->FirstChildElement(); current_element; 
            current_element = current_element->NextSiblingElement()) {
            string name = current_element->Name();
            /* cout << name << endl; */
            if ("title" == name) {
                string title = current_element->GetText();
                rss_it._title = RssReader::filter(title); 
                cout << "Title = " << rss_it._title << endl;
            }
            else if ("link" == name) {
                string link = current_element->GetText();
                rss_it._link = RssReader::filter(link); 
                cout << "Link = " << rss_it._link << endl;
            }
            else if ("description" == name) {
                string description = current_element->GetText();
                rss_it._description = RssReader::filter(description); 
                cout << "Description = " << rss_it._description << endl;
            }
            else if ("content:encoded" == name) {
                string content = current_element->GetText();
                rss_it._content = RssReader::filter(content); 
                cout << "Content = " << rss_it._content << endl;
            }
        }

        _rss.push_back(rss_it);
        item = item->NextSiblingElement();
    }
}

void RssReader::dump(const string &filename) {
    ofstream ofs(filename);
    if(!ofs.good()) {
        cerr << "State of ofstream is error" << endl;
        return;
    }

    for (size_t id = 0; id < _rss.size(); ++id) {
        ofs << "<doc>" << "\n"
        << "\t" << "<docid>" << id+1 << "</docid>" << endl
        << "\t" << "<title>" << _rss[id]._title << "</title>" << endl
        << "\t" << "<link>" << _rss[id]._link << "</link>"<< endl
        << "\t" << "<description>" << _rss[id]._description << "</description>" << endl
        << "\t" << "<content>" << _rss[id]._content << "</content>" << endl;
    }
}


