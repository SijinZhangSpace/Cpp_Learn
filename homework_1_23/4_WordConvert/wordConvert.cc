#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

class WordConvert
{
public:
    WordConvert()
    {
        ruleFile();
        converFile();
    }

    void ruleFile()
    {
        ifstream ifs_rule("map.txt");
        if(!ifs_rule.good())
        {
            cerr << "Rule File open failed!" << endl;
            return;
        }

        string word, cnv_word, spc;
        //     读入第一个单词      读入该行剩余内容 
        while(ifs_rule >> word && getline(ifs_rule, cnv_word))
        {
            deleSpace(cnv_word);
            auto it = _cnv_dict.find(word);
            if(it == _cnv_dict.end())
            {
                _cnv_dict.insert(pair<string, string>(word, cnv_word));
            }
        }
    }

    //去除首位空格
    void deleSpace(string &str)
    {
        str.erase(0,str.find_first_not_of(' '));
    }

    void converFile()
    {
        ifstream ifs_cnv("file.txt");
        if(!ifs_cnv.good())
        {
            cerr << "File to be converted open failed!" << endl;
        }

        string line, word, rst_word;
        while(getline(ifs_cnv, line))
        {
            istringstream iss(line);
            while(iss >> word)
            {
                auto it = _cnv_dict.find(word);
                if(it != _cnv_dict.end())
                {
                    word = it->second;
                }
                cout << word << " ";
            }
            cout << endl;
        }
    }
private:
    unordered_map<string, string> _cnv_dict;
};

void test()
{
    WordConvert wrd_cnv;
}

int main()
{
    test();
    return 0;
}

