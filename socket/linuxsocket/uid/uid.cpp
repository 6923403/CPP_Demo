#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    std::cout << "userid: " << uid << "  effective uid: " << euid << std::endl;

    /*
     * chown user:user uid
     * chmod +s uid
     * ./uid
     */
    return 0;
}
