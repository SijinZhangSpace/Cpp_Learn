#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory>
//#include <>

using namespace std;

class QueryResult
{
	friend ostream& print(ostream& os, const QueryResult& q);
public:
    typedef std::vector<std::string>::size_type line_num;
	typedef std::set<line_num>::const_iterator line_it;

	QueryResult(string word, shared_ptr<set<line_num>> lines, shared_ptr<vector<string>> file)
	: _word(word) 
    , _lines(lines)
    , _file(file) {}

    set<line_num>::size_type size() const
    {
        return _lines->size();
    }

    line_it begin() const
    {
        return _lines->begin();
    }

    line_it end() const
    {
        return _lines->end();
    }

    shared_ptr<vector<string>> get_file()
    {
        return _file;
    }

private:
	string _word;
	shared_ptr <set<line_num>> _lines;
	shared_ptr <vector<string>> _file;
};

ostream &print(ostream&, const QueryResult&);

#endif
