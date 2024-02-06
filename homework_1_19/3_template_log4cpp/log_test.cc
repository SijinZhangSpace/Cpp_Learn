#include <iostream>
#include <sstream>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include<log4cpp/Priority.hh>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostringstream;
using namespace log4cpp;

class Mylogger
{
public:
    static Mylogger *getInstance() {
        if(!_myLog)
        {
            /*PatternLayout *_ppl = new PatternLayout();
            _ppl->setConversionPattern("%d [%p] %c: %m %n");
            cout << "PatternLayout" << endl;

            OstreamAppender *_poa = new OstreamAppender("OstreamAppender", &cout);
            _poa->setLayout(_ppl);

            Category &root = Category::getRoot();
            root.addAppender(_poa);

            root.setPriority(Priority::INFO);*/

            BasicLayout *bscLyt = new BasicLayout();
            OstreamAppender *os = new OstreamAppender("OstreamAppender", &cout);
            os->setLayout(bscLyt);
            Category &root = Category::getRoot();
            root.addAppender(os);
            root.setPriority(Priority::DEBUG);

            _myLog = new Mylogger(root);
        }
        return _myLog;
    }

    static void destroy() {
        if(_myLog)
        {
            Category::shutdown();
            delete _myLog;
            _myLog = nullptr;
        }
    }

    template <typename ...Args>
    void warn(const char *msg, Args ...args) 
    {
        _rootctg.warn(msg, args...); //以warn级别输出日志信息
    }

    template <typename ...Args>
    void error(const char *msg ,Args ...args) 
    {
        _rootctg.error(msg, args...);
    }

    template <typename ...Args>
    void fatal(const char *msg ,Args ...args) {
        _rootctg.fatal(msg, args...);
    }

    template <typename ...Args>
    void crit(const char *msg ,Args ...args) {
        _rootctg.crit(msg, args...);
    }

    template <typename ...Args>
    void debug(const char *msg ,Args ...args) {
        _rootctg.debug(msg, args...);
    }

    template <typename ...Args>
    void info(const char *msg ,Args ...args) {
        _rootctg.info(msg, args...);
    }

private:
    Mylogger(Category &root)
    : _root(root)
    , _rootctg(Category::getInstance("log_test")) {}

    ~Mylogger(){}

private:
    static Mylogger *_myLog;
    Category &_root;
    Category &_rootctg;
};

Mylogger *Mylogger::_myLog = nullptr;

template <typename ...Args>
void LogInfo(const string &msg, Args ...args)
{
    Mylogger* pLog =  Mylogger::getInstance();
    pLog->info(msg.c_str(), args...);
    pLog->destroy();
}

template <typename ...Args>
void LogError(const string &msg , Args ...args){
    Mylogger* pLog =  Mylogger::getInstance();
    pLog->error(msg.c_str(), args...);
    pLog->destroy();
}

template <typename ...Args>
void LogWarn(const string &msg , Args ...args){
    Mylogger* pLog =  Mylogger::getInstance();
    pLog->warn(msg.c_str(), args...);
    pLog->destroy();
}

template <typename ...Args>
void LogDebug(const string &msg , Args ...args){
    Mylogger* pLog =  Mylogger::getInstance();
    pLog->debug(msg.c_str(), args...);
    pLog->destroy();
}

void test()
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    int number = 100;
	const char *pstr = "hello, log4cpp";
	LogInfo("This is an info message. number = %d, str = %s\n", number, pstr);
	LogError("This is an error message. number = %d, str = %s\n", number, pstr);
	LogWarn("This is a warn message. number = %d, str = %s\n", number, pstr);
	LogDebug("This is a debug message. number = %d, str = %s\n", number, pstr);
}

int main()
{
    test();
    return 0;
}

