#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::vector;
using std::set;
using std::map;
using std::string;
using std::shared_ptr;

using line_NO = vector<string>::size_type;
class QueryResult;	//前向声明
class TextQuery		//读取类
{
public:
	
	//读取指定输入的构造函数
	TextQuery(ifstream& i_file);
	//查询操作
	QueryResult query(const string& word)const;	//函数作用是：将读入的数据传给打印的类。
private:
	shared_ptr<vector<string>> file;			//拷贝文件内容
	map<string, shared_ptr<set<line_NO>>> wm;	//每个单词和它所出现的行号

};

class QueryResult	//打印类
{
	friend ostream& print(ostream& os, const QueryResult& q);	//作为类的友元函数
public:
	QueryResult(string s, shared_ptr<set<line_NO>> p, shared_ptr<vector<string>> f)
		:research(s), lines(p), file(f) {}	//接受来自读取的类的数据
private:
	string research;					//查询单词
	shared_ptr <set<line_NO>> lines;	//出现的行号，set集合
	shared_ptr <vector<string>> file;	//输入文件，vector容器
};


TextQuery::TextQuery(ifstream& i_file) :file(new vector<string>)
{
	string text;
	while (getline(i_file, text))
	{
		file->push_back(text);	//文件每一行存入vector
		auto No = file->size() - 1;
		istringstream line(text);	//读取这一行
		string word;
		while (line >> word)
		{
			//读取行的每个单词
			auto& lines = wm[word];//lines是一个shared_ptr
			if (!lines)
			{
				lines.reset(new set<line_NO>);	//分配一个新的set
			}
			lines->insert(No);	//将此行号插入到set中
		}
	}

}

QueryResult TextQuery::query(const string& word) const
{
	//未找到查询单词，定义一个空的set，
	static shared_ptr<set<line_NO>> nodata(new set<line_NO>);
	auto loc = wm.find(word);	//查找关键字
	if (loc == wm.end())		//返回一个指向这个关键字对应的所有的值的map迭代器
	{
		return QueryResult(word, nodata, file);	//将空set传入，表示未找到
	}
	else
	{
		return QueryResult(word, loc->second, file);	//传入关键字对应的set集合
	}
}

ostream& print(ostream& os, const QueryResult& q)
{
	//找到了单词，打印出现次数和所出现的位置
	//set的size成员函数返回set关键字的个数
	os << q.research << " occurs " << q.lines->size() << endl;	
	for (auto num : *q.lines)				//得到在set中对应的行号
	{
		//在文件中根据获得的行号来打印
		os << "\t(line " << num + 1 << ") " << *(q.file->begin() + num) << endl;
	}
	return os;
}

int main()
{
    string filename;
    cout << "Please input filename: ";
    cin >> filename;
	ifstream in_file(filename);
	TextQuery tq(in_file);
	while (true)
	{
		cout << "Please input word to query/\"quit\" to exit: ";
		string word;
		if (!(cin >> word) || word== "quit")
		{
			break;
		}
		print(cout, tq.query(word)) << endl;
	}
	return 0;
}

