#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::map;
using std::set;
using std::pair;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;


class TextQuery
{
public:
    void readFile(const string filename) {
        ifstream ifs(filename);
        if (!ifs.good()) {
            cerr << "ifstream is not good" << endl;
            return;
        }

        string line;
        string word;
        int line_num = 1;
        while (getline(ifs, line)) {
            _lines.push_back(line); //每行存入_lines
            convert(line);
            istringstream iss(line);
            while (iss >> word) {
                //单词和出现次数存入_dict
                map<string, int>::iterator ret_dict = _dict.find(word);
                if (ret_dict != _dict.end()) {
                    ret_dict->second++;
                }
                else {
                    _dict.insert(pair<string, int>(word, 1));
                }
                //单词和所在行数存入_wordNumbers
                map<string, set<int>>::iterator ret_wordNumbers = _wordNumbers.find(word);
                if (ret_wordNumbers != _wordNumbers.end()) {
                    ret_wordNumbers->second.insert(line_num);
                }
                else {
                    set<int> line_set = {line_num};
                    _wordNumbers.insert(pair<string, set<int>>(word, line_set));
                }
            }
            ++line_num;
        }
        ifs.close();
    }

    void query(const string& word) {
        map<string, int>::iterator ret_dict = _dict.find(word);
        if (ret_dict == _dict.end()) { //没有该单词
            cout << "Word \"" << word << "\" is not in this file !" << endl << endl;
        }
        else {
            map<string, set<int>>::iterator ret_wordNumbers = _wordNumbers.find(word);
            cout << word << " occours " << ret_dict->second << " times." << endl;
            for (auto it = ret_wordNumbers->second.begin(); it != ret_wordNumbers->second.end(); ++it) {
                cout << "(line " << *it << ") " << _lines[*it - 1] << endl;
            }
        }
    }

    void convert(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (isupper(str[i]))
                tolower(str[i]);
            if (ispunct(str[i]))
                str[i] = ' ';
        }
    }

private:
    vector<string> _lines; //读入每行
    map<string, set<int> > _wordNumbers; //单词所在行数
    map<string, int> _dict; //单词出现次数
};

//程序测试用例
int main(int argc, char* argv[])
{
    string text;
    string word;
    cout << "Please input name of file: ";
    cin >> text;
    cout << endl;
    cout << "Please input the word to query: ";
    cin >> word;
    cout << endl;

    TextQuery tq;
    tq.readFile(text);
    tq.query(word);
    return 0;
}

