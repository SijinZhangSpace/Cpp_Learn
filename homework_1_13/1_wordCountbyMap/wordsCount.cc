#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::map;
using std::pair;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

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

        while(ifs >> word){
            convert(word); //大小写和标点转换
            istringstream iss1(word); //转换后可能分成两个单词
            while(iss1 >> sig_word){ //依次通过字符串输入流读入
                auto it = _dict.begin();
                for (; it != _dict.end(); ++it){
                    if (it->first == word) {
                        it->second++;
                        break;
                    }
                }
                if (it == _dict.end()) {
                    _dict.insert(pair<string, int>(word, 1));
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

        for(auto it = _dict.begin(); it != _dict.end(); ++it) { //遍历字典
            ofs << "Word = " << it->first 
                << "; Frequence = " << it->second << endl; //将字典中记录打印至文件中
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

    map<string, int> _dict;
};

int main()
{
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("Word_Record.txt");
    return 0;
}

