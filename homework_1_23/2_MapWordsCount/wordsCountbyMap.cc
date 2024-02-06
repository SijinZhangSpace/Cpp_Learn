#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

class MyCount
{
public:
    MyCount()
    {
        readFile();
        //printResult();
    }

    void readFile()
    {
        cout << "Enter filename to count words Or Enter 'q' to quit: ";
        string filename;
        cin >> filename;
        while ("q" != filename)
        {
            ifstream ifs(filename);
            if (!ifs.good())
            {
                cerr << "File open failed!" << endl;
                return;
            }

            string line, word;
            while(getline(ifs, line))
            {
                convert(line);
                istringstream iss(line);
                while(iss >> word)
                {
                    auto it = _dict.find(word);
                    if (_dict.end() == it)
                    {
                        _dict.insert(pair<string, int>(word, 1));
                    }
                    else
                    {
                        it->second++;
                    }
                }
            }
            printResult();
            cout << "Enter filename to count words Or Enter 'q' to quit: ";
            cin >> filename;
        }
    }

    void printResult()
    {
        cout << "Enter word to count Or Enter 'q' to quit: ";
        string wordIn;
        cin >> wordIn;
        while ("q" != wordIn)
        {
            auto it = _dict.find(wordIn);
            if(_dict.end() == it)
            {
                cout << "\nNo word " << wordIn << " in opening file!" << endl;
            }
            else
            {
                cout << "\nWord: " << wordIn << "occurs (" << it->second << ") times in file." << endl;
            }
            cout << "\nEnter word to count Or Enter 'q' to quit: ";
            cin >> wordIn;
        }

    }

    void convert(string &word){
        for(size_t i = 0; i < word.size(); i++){
            if(isupper(word[i]))
            {
                if(!tolower(word[i]))
                {
                    cerr << "Error Convert!" << endl;
                    return;
                }
            }
            if(ispunct(word[i]))
            {
                word[i] = ' ';
            }
        }
    }

private:
    map<string, int> _dict;
};

void test()
{
    MyCount myCount;
}

int main()
{
    test();
    return 0;
}

