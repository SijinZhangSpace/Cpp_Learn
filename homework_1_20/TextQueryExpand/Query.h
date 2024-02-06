#ifndef __QUERY_H__
#define __QUERY_H__
#include <iostream>
#include <string>
#include <memory>
#include "TextQuery.h"

using std::string;
using std::shared_ptr;

class Query_Base
{
    friend class Query;
protected:
    using line_num = TextQuery::line_num;
    virtual ~Query_Base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

class Query
{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

public:
    Query(const string &);

    QueryResult eval(const TextQuery &tq) const
    {
        return _pqb->eval(tq);
    }

    string rep() const
    {
        return _pqb->rep();
    }

private:
    Query(shared_ptr<Query_Base> query)
    : _pqb(query) {}

    shared_ptr<Query_Base> _pqb;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query) 
{
	return os << query.rep(); 
}

class WordQuery
: public Query_Base
{
    friend class Query;
    WordQuery(const string &str)
    : query_word(str) {}

    QueryResult eval(const TextQuery &tq) const
    {
        return tq.query(query_word);
    }

    string rep() const
    {
        return query_word;
    }

    string query_word;
};

inline
Query::Query(const string &str)
: _pqb(new WordQuery(str)) {}

class NotQuery
:public Query_Base
{
    friend class Query operator~(const Query &);
    NotQuery(const Query &q)
    : _q(q) {}

    string rep() const
    {
        return "~(" + _q.rep() + ")";
    }

    QueryResult eval(const TextQuery &) const;

    Query _q;
};

inline
Query operator~(const Query &opq)
{
    return shared_ptr<Query_Base> (new NotQuery(opq));
}

class BinaryQuery
:public Query_Base
{
protected:
    BinaryQuery(const Query &lop, const Query &rop, string op)
    : _lop(lop)
    , _rop(rop)
    , _op(op) {}

    string rep() const
    {
        return "(" + _lop.rep() + " " + _op + " " + _rop.rep() + ")";
    }

    Query _lop, _rop; //左右操作数
    string _op; //运算符
};

class AndQuery
:public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);

    AndQuery(const Query &lop, const Query &rop)
    : BinaryQuery(lop, rop, "&") {}

    QueryResult eval(const TextQuery &) const;
};

inline
Query operator&(const Query &lop, const Query &rop)
{
    return shared_ptr<Query_Base>(new AndQuery(lop, rop));
}

class OrQuery
: public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &lop, const Query &rop)
    : BinaryQuery(lop, rop, "|") {}

    QueryResult eval(const TextQuery &) const;
};

inline
Query operator|(const Query &lop, const Query &rop)
{
    return shared_ptr<Query_Base>(new OrQuery(lop, rop));
}

std::ifstream& open_file(std::ifstream&, const std::string&);
ifstream get_file(const string &);
bool get_word(std::string &);
bool get_words(std::string &, std::string &);
std::ostream &print(std::ostream&, const QueryResult&);

#endif /*__QUERY_H__*/
