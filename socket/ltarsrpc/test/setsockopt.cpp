#include <sys/types.h>
#include <sys/socket.h>


int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);


int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);

参数：
sock：将要被设置或者获取选项的套接字。
level：选项所在的协议层。
optname：需要访问的选项名。
optval：对于getsockopt()，指向返回选项值的缓冲。对于setsockopt()，指向包含新选项值的缓冲。
optlen：对于getsockopt()，作为入口参数时，选项值的最大长度。作为出口参数时，选项值的实际长度。对于setsockopt()，现选项的长度。

Re:
https://www.cnblogs.com/eeexu123/p/5275783.html
