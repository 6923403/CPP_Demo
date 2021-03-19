#include "logger.h"
logger::logger()
{
    memset(&m_dir_name, '\0', sizeof(m_dir_name));
    memset(&m_file_name, '\0', sizeof(m_file_name));
    set_log_file();
}

logger::~logger()
{
}

logger* logger::get_instance()
{
    static logger log;
    return &log;
}

void logger::set_log_file()
{
    time_t t = time(NULL);
    struct tm *sys_tm = localtime(&t);
    struct tm my_tm = *sys_tm;
    snprintf(m_file_name, 128, "./%d_%d_%2d_%2d-%s", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, my_tm.tm_hour, "Server.log");
}

void logger::write_log(int level, std::string text)
{

    outfile.open(m_file_name, std::ios::out | std::ios::app);
    std::string sig_info;
    switch (level) {
        case 0:
            sig_info = "Debug";
            break;
        case 1:
            sig_info = "Error";
            break;
        case 2:
            sig_info = "Warning";
            break;
        case 3:
            sig_info = "Info";
            break;
        default:
            break;
    }

    outfile << sig_info << ": " << text << std::endl;

    outfile.close();

}

/*
void logger::log_test() {
    LOG_DEBUG(0, "DEBUG");
    LOG_ERROR(1, "ERROR");
    LOG_WARN(2, "WARING");
}
*/