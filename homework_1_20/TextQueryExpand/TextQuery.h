#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "QueryResult.h"

using namespace std;

class QueryResult;

class TextQuery
{
public:
    using line_num = vector<std::string>::size_type;
	TextQuery(ifstream &);
    QueryResult query(const string&) const; 
    void display_map();

private:
    shared_ptr<vector<string> > file; 
    map<string, shared_ptr<set<line_num> > > wm;  

    static string cleanup_str(const string &);
};

#endif
