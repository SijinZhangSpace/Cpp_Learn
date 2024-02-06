#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

class judgeBracket{
public:
    judgeBracket(const string s)
    : s(s) {}

    bool isValid() {
        stack<char> st;
        for(size_t i = 0; i < s.size(); ++i)
        {
            if('(' == s[i] || '[' == s[i] || '{' == s[i])
            {
                st.push(s[i]);
            }
            else
            {
                if(!st.empty())
                {
                    if(')' == s[i])
                    {
                        if('(' == st.top()) st.pop();
                        else return false;
                    }
                    else if(']' == s[i])
                    {
                        if('[' == st.top()) st.pop();
                        else return false;            
                    }
                    else if ('}' == s[i])
                    {
                        if('{' == st.top()) st.pop();
                        else return false;
                    }
                }
                else return false;
                
            }
        }
        if(st.empty()) return true;
        else return false;
    }

private:
    string s;
};

int main()
{
    string s;
    cin >> s;
    judgeBracket judge(s);
    if(judge.isValid()) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}

