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

void test(){
    BasicLayout *_bsc_lyt1 = new BasicLayout();
    BasicLayout *_bsc_lyt2 = new BasicLayout();
    BasicLayout *_bsc_lyt3 = new BasicLayout();

    OstreamAppender *_osa = new OstreamAppender("OsA", &cout);
    _osa->setLayout(_bsc_lyt1);

    FileAppender *_fla = new FileAppender("File", "config.file");
    _fla->setLayout(_bsc_lyt2);

    RollingFileAppender *_rfa = new RollingFileAppender("RollingFile", "config.rolling",
                                                        10 * 1024, 9);
    _rfa->setLayout(_bsc_lyt3);

    Category &root = Category::getRoot().getInstance("log");
    root.addAppender(_osa);
    root.addAppender(_fla);
    root.addAppender(_rfa);

    root.setPriority(Priority::INFO);

    root.warn("Warn Message");
    root.error("Error Message");
    root.debug("Debug Message");
    root.info("Info Message");

    Category::shutdown();
}

int main()
{
    test();
    return 0;
}

