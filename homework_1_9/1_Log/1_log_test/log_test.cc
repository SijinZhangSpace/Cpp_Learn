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
            PatternLayout *_pl = new PatternLayout();
            _pl->setConversionPattern("%d [%p] %c: %m %n");
            cout << "PatternLayout" << endl;

            RollingFileAppender *_rf = new RollingFileAppender("file", "record.txt",
                                                               10 * 1024, 9);
            _rf->setLayout(_pl);
            cout << "RollingFileAppender" << endl;

            Category &root = Category::getRoot();
            root.addAppender(_rf);
            cout << "addAppender" << endl;

            root.setPriority(Priority::INFO);
            cout << "setPriority" << endl;

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

    void warn(const char *msg) {
        string file_name = __FILE__; //获取文件名
        size_t line_num = __LINE__; //行号
        string func_name = __func__; //函数名
        
        ostringstream ostr; //日志信息暂存串输出流
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.warn(ostr.str().c_str()); //以warn级别输出日志信息
    }

    void error(const char *msg) {
        string file_name = __FILE__;
        size_t line_num = __LINE__;
        string func_name = __func__;
        
        ostringstream ostr;
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.error(ostr.str().c_str());
    }

    void fatal(const char *msg) {
        string file_name = __FILE__;
        size_t line_num = __LINE__;
        string func_name = __func__;
        
        ostringstream ostr;
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.fatal(ostr.str().c_str());
    }

    void crit(const char *msg) {
        string file_name = __FILE__;
        size_t line_num = __LINE__;
        string func_name = __func__;
        
        ostringstream ostr;
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.crit(ostr.str().c_str());
    }

    void debug(const char *msg) {
        string file_name = __FILE__;
        size_t line_num = __LINE__;
        string func_name = __func__;
        
        ostringstream ostr;
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.debug(ostr.str().c_str());
    }

    void info(const char *msg) {
        string file_name = __FILE__;
        size_t line_num = __LINE__;
        string func_name = __func__;
        
        ostringstream ostr;
        ostr << "FileName: " << file_name << "; Line: " << line_num 
             << "; InFunc: " << func_name << " || " << msg;

        _rootctg.info(ostr.str().c_str());
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

void test0() {
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->warn("The log is warn message");
    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");

    log->destroy();
}

void LogInfo(const string &msg){
    BasicLayout *bscLyt = new BasicLayout();
    OstreamAppender *os = new OstreamAppender("OstreamAppender", &cout);
    os->setLayout(bscLyt);
    Category &root = Category::getRoot().getInstance("log_print");
    root.addAppender(os);
    root.setPriority(Priority::INFO);
    root.info(msg);
    Category::shutdown();
}

void LogError(const string &msg){
    BasicLayout *bscLyt = new BasicLayout();
    OstreamAppender *os = new OstreamAppender("OstreamAppender", &cout);
    os->setLayout(bscLyt);
    Category &root = Category::getRoot().getInstance("log_print");
    root.addAppender(os);
    root.setPriority(Priority::INFO);
    root.error(msg);
    Category::shutdown();
}

void LogWarn(const string &msg){
    BasicLayout *bscLyt = new BasicLayout();
    OstreamAppender *os = new OstreamAppender("OstreamAppender", &cout);
    os->setLayout(bscLyt);
    Category &root = Category::getRoot().getInstance("log_print");
    root.addAppender(os);
    root.setPriority(Priority::INFO);
    root.warn(msg);
    Category::shutdown();
}

void LogDebug(const string &msg){
    BasicLayout *bscLyt = new BasicLayout();
    OstreamAppender *os = new OstreamAppender("OstreamAppender", &cout);
    os->setLayout(bscLyt);
    Category &root = Category::getRoot().getInstance("log_print");
    root.addAppender(os);
    root.setPriority(Priority::INFO);
    root.debug(msg);
    Category::shutdown();
}

void test1()
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

int main()
{
    test0();
    test1();
    return 0;
}

