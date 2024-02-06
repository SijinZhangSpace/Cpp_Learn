#include <iostream>
#include <algorithm>
#include <set>
#include <memory>
#include <cstddef>
#include <iterator>
#include <vector>
#include <string>
#include "Query.h"
#include "TextQuery.h"

using std::cerr;
using std::inserter;
using std::set_intersection;
using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::ostream;
using std::shared_ptr; 

QueryResult NotQuery::eval(const TextQuery& text) const
{
    QueryResult result = _q.eval(text);

    shared_ptr<set<line_num> > ret_lines(new set<line_num>);

	QueryResult::line_it beg = result.begin(), end = result.end();

	vector<string>::size_type sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult
AndQuery::eval(const TextQuery& text) const
{
    QueryResult left = _lop.eval(text), right = _rop.eval(text);

    shared_ptr<set<line_num> > ret_lines(new set<line_num>);

    set_intersection(left.begin(), left.end(),
                   right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
OrQuery::eval(const TextQuery& text) const
{
    QueryResult right = _rop.eval(text), left = _lop.eval(text);

	shared_ptr<set<line_num> >
		ret_lines(new set<line_num>(left.begin(), left.end()));

	ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}

ifstream get_file(const string &filename)
{
	ifstream infile(filename);
    if (!infile.good()) {
        cerr << "Open File Failed" << endl;
    }

    return infile;
}

bool get_word(string &s1)
{
    cout << "enter a word to search for, or q to quit: ";
    cin >> s1;
    if (!cin || s1 == "q") return false;
    else return true;
}

bool get_words(string &s1, string &s2)
{

    cout << "enter two words to search for, or q to quit: ";
    cin  >> s1;

    if (!cin || s1 == "q")
        return false;
    cin >> s2;
    return true;
}
