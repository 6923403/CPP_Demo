#ifndef CPP_DEMO_LOGGER_H
#define CPP_DEMO_LOGGER_H

/*
 * 全局可用 单例模式
 * log级别
 * 输出位置 文件名
 */

#include <string>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <unistd.h>

class logger {
public:
    enum LOGLEVEL
    {
        LOG_LEVEL_DEBUG,     // debug
        LOG_LEVEL_ERROR,     // error
        LOG_LEVEL_WARNING,   // warning
        LOG_LEVEL_INFO,      // info
    };

    enum LOGTARGET //输出模式
    {
        LOG_TARGET_NONE ,
        log_target_console,
        log_target_file,
    };

    logger();
    ~logger();

    static logger* get_instance();
    void log_init();
    void set_log_file();
    void set_log_level();
    void write_log(int level, std::string text);
    void log_test();

private:
    std::ofstream outfile;
    bool m_new_file;
    char m_dir_name[128];
    char m_file_name[128];

};

#define LOG_DEBUG(a, text) \
        logger::get_instance()->write_log(a, text);
#define LOG_ERROR(a, text) \
        logger::get_instance()->write_log(a, text);
#define LOG_WARN(a, text)  \
        logger::get_instance()->write_log(a, text);
#define LOG_INFO(a, text)  \
        logger::get_instance()->write_log(a, text);

#endif //CPP_DEMO_LOGGER_H
