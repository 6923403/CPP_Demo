#include "logger.h"

int main()
{
    /*
     * logger logg;
    logg.log_test();
    */
    LOG_DEBUG(0, "DEBUG");
    LOG_ERROR(1, "ERROR");
    LOG_WARN(2, "WARING");
    LOG_INFO(3, "INFO");

    return 0;
}
