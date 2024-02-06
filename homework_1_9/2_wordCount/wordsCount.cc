#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record
{
	string _word;
	int _frequency;

    //重载运算符以判断字典中有无记录
    bool operator == (const Record &rcd){
        //只需判断单词是否已经存在
        return rcd._word == _word;
    }
};

class Dictionary
{
public:
    //读文件并存入vector
    void read(const string &filename){
        ifstream ifs(filename);
        if (!ifs.good()){ //流状态不为goodbit则报错
            cerr << "State of ifstream is error" << endl;
        }

        string word; //存储从文件中读取到的由空格间隔的单词
        string sig_word; //将读取到的单词写入struct
        bool temp = 0; //标记是否有新记录加入字典

        while(ifs >> word){
            convert(word); //大小写和标点转换
            istringstream iss1(word); //转换后可能分成两个单词
            while(iss1 >> sig_word){ //依次通过字符串输入流读入
                //cout << "SingleWord = " << sig_word << endl;
                Record rcd;
                rcd._word = sig_word;
                for(size_t i=0; i < _dict.size(); i++){ //遍历字典
                    if(_dict[i] == rcd){ //单词已存在
                        _dict[i]._frequency++; //次数加1
                        temp = 1; //标记改为真
                    }
                }
                if(temp){ //有新增记录
                    temp = 0; //重置标记
                }
                else{ //否则
                    rcd._frequency = 1; //新单词次数记1
                    _dict.push_back(rcd); //加入字典
                }
            }
        }

        ifs.close();
    }

    //将字典中记录写入文件
    void store(const string &filename){
        ofstream ofs(filename);
        if(!ofs.good()){
            cerr << "State of ofstream is error" << endl;
            return;
        }

        for(size_t i=0; i < _dict.size(); i++){ //遍历字典
            ofs << "Word = " << _dict[i]._word 
                << "; Frequence = " << _dict[i]._frequency << endl; //将字典中记录打印至文件中
        }

        ofs.close();
    }

    //大写字母转小写
    void convert(string &str){
        for(int i = 0; i < str.size(); i++){
            if(isupper(str[i]))
                tolower(str[i]);
            if(ispunct(str[i]))
                str[i] = ' ';
        }
    }

private:

    vector<Record> _dict;
};

int main()
{
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("Word_Record.txt");
    return 0;
}

