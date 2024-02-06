#include <cstddef>
#include <memory> 
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <utility>
#include "TextQuery.h"

using std::size_t;
using std::shared_ptr;
using std::istringstream;
using std::string;
using std::getline;
using std::vector;
using std::map;
using std::set;
using std::cerr;
using std::cout;
using std::cin;
using std::ostream;
using std::endl;
using std::ifstream;
using std::ispunct;
using std::tolower;
using std::strlen;
using std::pair;

inline
string make_plural(size_t ctr, const string &word, const string &ending)
{
	return (ctr > 1) ? word + ending : word;
}

typedef map<string, shared_ptr<set<TextQuery::line_num> > > wmType;

typedef wmType::const_iterator wmIter;

typedef shared_ptr<set<TextQuery::line_num> > lineType;

typedef set<TextQuery::line_num>::const_iterator lineIter;

TextQuery::TextQuery(ifstream &is)
: file(new vector<string>)
{
    string text;
    while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;               
		while (line >> word) {
            word = cleanup_str(word);
            lineType &lines = wm[word];
            if (!lines)
                lines.reset(new set<line_num>);
            lines->insert(n);
		}
	}
}

string TextQuery::cleanup_str(const string &word)
{
    string ret;
    for (string::const_iterator it = word.begin(); it != word.end(); ++it) 
	{
        if (!ispunct(*it))
            ret += tolower(*it);
    }
    return ret;
}

QueryResult
TextQuery::query(const string &_word) const
{
	static lineType nodata(new set<line_num>); 

    wmIter loc = wm.find(cleanup_str(_word));

	if (loc == wm.end()) 
		return QueryResult(_word, nodata, file);
	else 
		return QueryResult(_word, loc->second, file);
}

ostream &print(ostream & os, const QueryResult &qr)
{
    os << qr._word << " occurs " << qr._lines->size() << " "
       << make_plural(qr._lines->size(), "time", "s") << endl;

	for (lineIter num = qr._lines->begin();
				num != qr._lines->end(); ++num) 
        os << "\t(line " << *num + 1 << ") " 
		   << *(qr._file->begin() + *num) << endl;
	return os;
}

void TextQuery::display_map()
{
    wmIter iter = wm.begin(), iter_end = wm.end();

    for ( ; iter != iter_end; ++iter) {
        cout << "word: " << iter->first << " {";

        lineType text_locs = iter->second;
        lineIter loc_iter = text_locs->begin(),
                        loc_iter_end = text_locs->end();

        while (loc_iter != loc_iter_end)
        {
            cout << *loc_iter;

            if (++loc_iter != loc_iter_end)
                 cout << ", ";

         }

         cout << "}\n";
    }
    cout << endl;
}
