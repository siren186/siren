/**
 * 死人
 * siren186@163.com
 * 2014-05-13
 * 
 * 
 * 编译boost步骤(当然bjam再强大,我也不会用,简单就好)
 * 1. 运行bootstrap.bat, 生成bjam.exe
 * 2. 使用bjam.exe编译生成相应的boost库.例:
 *  用法1:
 *      bjam toolset=msvc-10.0 install  ///> 全部安装(版本VC10),会将生成的文件,拷贝至C:\Boost.文件生成在bin.v2下.
 *  用法2:
 *      bjam toolset=msvc-8.0 stage    ///> 全部安装(版本VC8),不会在C盘下生成相应东西,文件存在boost下的的bin.v2文件夹内
 *  用法3:
 *      bjam toolset=msvc-10.0 --with-regex stage       ///> 仅编译regexp库,其它库不编译.省时间
 *  用法4:
 *      bjam toolset=msvc-10.0 --without-python stage   ///> 不编译python库
 *      
 *  用法5:
 *      bjam toolset=msvc-10.0 --with-regex stage debug release threading=multi threading=single link=shared link=static runtime-link=shared runtime-link=static
 *      
 *      
 *  将生成的相应库文件,拷贝至siren工程目录:\output\lib\下,方可正常编译本代码.
 */

#include <iostream> 
#include "gtest/gtest.h"
#include <boost/thread.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

void thread() 
{ 
    for (int i = 0; i < 5; ++i) 
    { 
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        std::cout << i << std::endl; 
    } 
} 

int main(int argc, char **argv)
{ 
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Boost, Thread)
{
    boost::thread t(thread); 
    t.join();
}

TEST(Boost, Log)
{
    boost::log::add_file_log("c:\\siren_boost.log");

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info); ///> 过滤info及以下级别
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}
